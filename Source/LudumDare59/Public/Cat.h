// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Cat.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCat, Log, All);

UCLASS()
class LUDUMDARE59_API ACat : public AActor
{
    GENERATED_BODY()
    
public:    
    ACat();

    UFUNCTION(BlueprintCallable, Category = "Cat Interaction")
    void UpdatePickupProgress(float Progress);

    UFUNCTION(BlueprintCallable, Category = "Cat Interaction")
    void CompletePickup();

    UFUNCTION(BlueprintCallable, Category = "Cat Interaction")
    void CancelPickup();

    UFUNCTION(BlueprintCallable, Category = "Cat Logic")
    void SetScared(bool bNewScared);

    UFUNCTION(BlueprintImplementableEvent, Category = "Cat Interaction")
    void OnCatPickedUp();

    UFUNCTION(BlueprintImplementableEvent, Category = "Cat Interaction")
    void OnPickupProgressUpdate(float Progress);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cat Components")
    USphereComponent* PresenceSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cat Components")
    UStaticMeshComponent* CatMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cat Components")
    UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cat Sounds")
    USoundAttenuation* MeowAttenuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cat Sounds")
    USoundBase* HappySound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cat Sounds")
    USoundBase* ScaredSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cat Settings")
    float MinMeowDelay = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cat Settings")
    float MaxMeowDelay = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cat Settings")
    bool bIsScared;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void PlayMeow();
    FTimerHandle MeowTimerHandle;
};
