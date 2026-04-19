// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"

#include "EZombieState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>


int AZombieBase::MeleeAttack_Implementation()
{
    if (AttackMontage)
    {
        PlayAnimMontage(AttackMontage);
        // Порада: PerformMeleeHit() краще викликати через AnimNotify в монтежі, 
        // щоб удар ставався саме тоді, коли зомбі махає рукою.
        // Але для тесту можна викликати прямо тут:
        //PerformMeleeHit();
    }
    return 0;
}

void AZombieBase::PerformMeleeHit()
{
    FVector Start = GetActorLocation() + GetActorForwardVector() * 40.f;
    FVector End = Start + GetActorForwardVector() * AttackRange;

    FHitResult HitResult;
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    bool bHit = UKismetSystemLibrary::SphereTraceSingle(
        this,
        Start,
        End,
        AttackRadius,
        UEngineTypes::ConvertToTraceType(ECC_Pawn),
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration,
        HitResult,
        true
    );

    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            UGameplayStatics::ApplyDamage(
                HitActor,
                AttackDamage,
                GetController(),
                this,
                UDamageType::StaticClass()
            );

            UE_LOG(LogTemp, Log, TEXT("Zombie hit: %s for %f damage"), *HitActor->GetName(), AttackDamage);
        }
    }
}

void AZombieBase::SetUpStimuliSource()
{
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimuliSourceComponent)
	{
		StimuliSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourceComponent->RegisterWithPerceptionSystem();
	}
}

void AZombieBase::SetNpcState(const EZombieState State)
{
	NpcState = State;
	switch (State)
	{
	case EZombieState::ETIP_IDLE:
		GetCharacterMovement()->MaxWalkSpeed =40.f;
		break;;
	case EZombieState::ETIP_ROAM:
		GetCharacterMovement()->MaxWalkSpeed =40.f;
		break;
	case EZombieState::ETIP_SEARCH:
		GetCharacterMovement()->MaxWalkSpeed =40.f;
		break;
	case EZombieState::ETIP_CHASE:
		GetCharacterMovement()->MaxWalkSpeed =75.f;
		break;
	case EZombieState::ETIP_HYPER_CHASE:
		GetCharacterMovement()->MaxWalkSpeed =350.f;
		break;
	default:
		break;
	}
}

// Sets default values
AZombieBase::AZombieBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();
	NpcState = EZombieState::ETIP_ROAM;
}

// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
