// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeadDelegate);

UCLASS()
class LUDUMDARE59_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:

	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerDeadDelegate OnPlayerDead;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

protected:
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Ћог≥ка смерт≥
	void Die();

	bool bIsDead = false;

};
