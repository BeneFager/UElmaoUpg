#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyHealthOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUCK_API UEnemyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void TakeDamage(float DamageAmount);

	UPROPERTY(BlueprintAssignable)
	FEnemyHealthOnDeath OnDeath;

	UPROPERTY(BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 4.f;
};
