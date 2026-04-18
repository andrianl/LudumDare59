// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EZombieState.h"
#include "BTTask_UpdateNPCState.generated.h"

UCLASS()
class LUDUMDARE59_API UBTTask_UpdateNPCState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Zombie State", meta=(AllowPrivateAccess="true"))
	EZombieState State;

public:
	explicit UBTTask_UpdateNPCState(const FObjectInitializer& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
