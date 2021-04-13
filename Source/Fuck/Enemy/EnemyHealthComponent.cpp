#include "EnemyHealthComponent.h"

void UEnemyHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

void UEnemyHealthComponent::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.f)
	{
		Health = 0.f;
		OnDeath.Broadcast();
	}

	UE_LOG(LogTemp, Log, TEXT("Health: %f/%f"), Health, MaxHealth);
}
