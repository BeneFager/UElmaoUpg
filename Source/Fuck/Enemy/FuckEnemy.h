#pragma once
#include "GameFramework/Actor.h"
#include "FuckEnemy.generated.h"
class USphereComponent;
class UFuckProjectileResponseComponent;
class UEnemyHealthComponent;

UCLASS()
class AFuckEnemy : public AActor
{
	GENERATED_BODY()
		
public:
	AFuckEnemy();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UFUNCTION()
	void HandleDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UEnemyHealthComponent* HealthComp;

	UPROPERTY(EditInstanceOnly)
	float Speed = 50.f;
};