// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UniqueSpawnManager.generated.h"

UCLASS()
class LUDUMDARE59_API AUniqueSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUniqueSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ProcessUniqueSpawns();
};
