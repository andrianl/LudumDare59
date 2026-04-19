#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead) return 0.0f;

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= ActualDamage;

	UE_LOG(LogTemp, Log, TEXT("Player took damage: %f. Current Health: %f"), ActualDamage, Health);

	if (FMath::IsNearlyZero(Health) || Health < 0)
	{
		Die();
	}

	return ActualDamage;
}

void APlayerCharacter::Die()
{
	if (bIsDead) return;

	bIsDead = true;
	Health = 0.0f;

	UE_LOG(LogTemp, Warning, TEXT("Player is DEAD!"));

	if (OnPlayerDead.IsBound())
	{
		OnPlayerDead.Broadcast();
	}

	//GetMesh()->SetSimulatePhysics(true);
	//GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
}