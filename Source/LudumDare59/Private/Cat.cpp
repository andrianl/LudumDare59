#include "Cat.h"
#include "TimerManager.h"
#include "Sound/SoundAttenuation.h"

// Визначаємо категорію
DEFINE_LOG_CATEGORY(LogCat);

ACat::ACat()
{
    CatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CatMesh"));
    RootComponent = CatMesh;

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MeowAudioSource"));
    AudioComponent->SetupAttachment(RootComponent);

    AudioComponent->bAutoActivate = false;

    PrimaryActorTick.bCanEverTick = false;
}

void ACat::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherActor->IsA(APawn::StaticClass()))
    {
        UE_LOG(LogCat, Log, TEXT("Player entered sphere. Cat is HAPPY."));

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                FString::Printf(TEXT("Player entered sphere. Cat is HAPPY.")));
        }

        SetScared(false);
    }
}

void ACat::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this && OtherActor->IsA(APawn::StaticClass()))
    {
        UE_LOG(LogCat, Log, TEXT("Player left sphere. Cat is SCARED."));

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta,
				FString::Printf(TEXT("Player left sphere. Cat is SCARED.")));
        }

        SetScared(true);
    }
}


void ACat::SetScared(bool bNewScared)
{
    bIsScared = bNewScared;

    GetWorldTimerManager().ClearTimer(MeowTimerHandle);
    PlayMeow();
}

void ACat::BeginPlay()
{
    Super::BeginPlay();

    if (IsValid(MeowAttenuation))
    {
        AudioComponent->AttenuationSettings = MeowAttenuation;
    }

    float InitialDelay = FMath::FRandRange(MinMeowDelay, MaxMeowDelay);
    GetWorldTimerManager().SetTimer(MeowTimerHandle, this, &ACat::PlayMeow, InitialDelay, false);
}

void ACat::PlayMeow()
{
    // 1. Визначаємо, який звук маємо грати
    USoundBase* SoundToPlay = bIsScared ? ScaredSound : HappySound;
    FString StateStr = bIsScared ? TEXT("SCARED") : TEXT("HAPPY");

    // 2. Лог на екран про початок спроби (синій колір)
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan,
            FString::Printf(TEXT("Cat attempts to meow. State: %s"), *StateStr));
        UE_LOG(LogCat, Display, TEXT("Cat attempts to meow. State: %s"), *StateStr);
    }

    // 3. Детальна перевірка компонентів
    if (!AudioComponent)
    {
        UE_LOG(LogCat, Error, TEXT("CAT ERROR: AudioComponent is NULL on %s!"), *GetName());
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CAT ERROR: AudioComponent is MISSING!"));
    }
    else if (!SoundToPlay)
    {
        UE_LOG(LogCat, Warning, TEXT("CAT WARNING: No sound assigned for state %s on %s!"), *StateStr, *GetName());
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
            FString::Printf(TEXT("CAT WARNING: %s sound is not set in Blueprint!"), *StateStr));
    }
    else
    {
        // Усе добре, намагаємося відтворити
        AudioComponent->SetSound(SoundToPlay);

        if (AudioComponent->IsPlaying())
        {
            AudioComponent->Stop();
        }

        AudioComponent->Play();

        // Лог успіху (зелений колір)
        UE_LOG(LogCat, Log, TEXT("CAT SUCCESS: Playing %s sound (%s)"), *StateStr, *SoundToPlay->GetName());
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,
                FString::Printf(TEXT("Cat MEOW: %s (%s)"), *StateStr, *SoundToPlay->GetName()));
        }
    }

    // 4. Лог таймера
    float NextDelay = FMath::FRandRange(MinMeowDelay, MaxMeowDelay);
    GetWorldTimerManager().SetTimer(MeowTimerHandle, this, &ACat::PlayMeow, NextDelay, false);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan,
            FString::Printf(TEXT("Next meow in %f seconds"), NextDelay));
    }

    UE_LOG(LogCat, Verbose, TEXT("CAT: Next meow in %f seconds"), NextDelay);
}