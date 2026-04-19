// Fill out your copyright notice in the Description page of Project Settings.


#include "UniqueSpawnManager.h"
#include "BoxSpawner.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AUniqueSpawnManager::AUniqueSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AUniqueSpawnManager::BeginPlay()
{
	Super::BeginPlay();

	ProcessUniqueSpawns();
}

void AUniqueSpawnManager::ProcessUniqueSpawns()
{
    TArray<AActor*> FoundSpawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoxSpawner::StaticClass(), FoundSpawners);

    TMap<TSubclassOf<AActor>, TArray<ABoxSpawner*>> UniqueGroups;

    for (AActor* Actor : FoundSpawners)
    {
        ABoxSpawner* Spawner = Cast<ABoxSpawner>(Actor);
        if (Spawner && Spawner->SpawnType == ESpawnType::Unique && Spawner->ActorToSpawn)
        {
            UniqueGroups.FindOrAdd(Spawner->ActorToSpawn).Add(Spawner);
        }
    }

    for (auto& Elem : UniqueGroups)
    {
        TArray<ABoxSpawner*>& Group = Elem.Value;
        if (Group.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, Group.Num() - 1);
            Group[RandomIndex]->SpawnActors();

            UE_LOG(LogTemp, Warning, TEXT("Manager selected 1 spawner for %s out of %d points"),
                *Elem.Key->GetName(), Group.Num());
        }
    }
}


