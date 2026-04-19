// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BoxSpawner.generated.h"

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
    Normal UMETA(DisplayName = "Normal (Always Spawns)"),
    Unique UMETA(DisplayName = "Unique (Only one from group)")
};

UCLASS()
class LUDUMDARE59_API ABoxSpawner : public AActor
{
    GENERATED_BODY()
    
public:    
    ABoxSpawner();

    void SpawnActors();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TSubclassOf<AActor> ActorToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    ESpawnType SpawnType = ESpawnType::Normal;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawnArea;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    int32 AmountToSpawn = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    ESpawnActorCollisionHandlingMethod CollisionHandle = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

private:
    FVector GetRandomPointInBox() const;
};
