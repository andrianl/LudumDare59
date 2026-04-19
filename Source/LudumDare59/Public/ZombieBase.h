// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EZombieState.h"
#include "ZombieActionInterface.h"
#include "GameFramework/Character.h"
#include "ZombieBase.generated.h"

UCLASS()
class LUDUMDARE59_API AZombieBase : public ACharacter, public IZombieActionInterface
{
public:
	virtual int MeleeAttack_Implementation() override;
private:
	GENERATED_BODY()

private:
	class UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;
	void SetUpStimuliSource();
	EZombieState NpcState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Montage", meta=(AllowPrivateAccess="true"))
	UAnimMontage* AttackMontage;
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EZombieState GetNpcState() const
	{
		return NpcState;
	}  

	void SetNpcState(const EZombieState State);
	// Sets default values for this character's properties
	AZombieBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie Attack")
    float AttackDamage = 20.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie Attack")
    float AttackRange = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie Attack")
    float AttackRadius = 40.f;

    UFUNCTION(BlueprintCallable, Category = "Zombie Attack")
    void PerformMeleeHit();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
