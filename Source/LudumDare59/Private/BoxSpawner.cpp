// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxSpawner.h"
#include "Kismet/KismetMathLibrary.h"

ABoxSpawner::ABoxSpawner()
{
    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    RootComponent = SpawnArea;

    SpawnArea->ShapeColor = FColor::Cyan;

    PrimaryActorTick.bCanEverTick = false;
}

void ABoxSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (IsValid(ActorToSpawn))
    {
        SpawnActors();
    }
}

void ABoxSpawner::SpawnActors()
{
    UWorld* const World = GetWorld();
    if (!IsValid(World)) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();
    SpawnParams.SpawnCollisionHandlingOverride = CollisionHandle;

    for (int32 i = 0; i < AmountToSpawn; i++)
    {
        const FVector RandomLocation = GetRandomPointInBox();

        const FRotator RandomRotation = FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f);

        World->SpawnActor<AActor>(ActorToSpawn, RandomLocation, RandomRotation, SpawnParams);
    }
}

FVector ABoxSpawner::GetRandomPointInBox() const
{
    FVector BoxOrigin = SpawnArea->GetComponentLocation();
    FVector BoxExtent = SpawnArea->GetScaledBoxExtent();

    return UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);
}