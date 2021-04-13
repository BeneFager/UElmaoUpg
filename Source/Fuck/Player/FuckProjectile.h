#pragma once
#include "GameFramework/Actor.h"
#include "FuckProjectile.generated.h"
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class AFuckProjectile : public AActor
{
	GENERATED_BODY()

public:
	AFuckProjectile();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DoVeryCoolThing();

	UFUNCTION(BlueprintPure)
	float GetSuperCoolNumber();

	UFUNCTION(BlueprintImplementableEvent)
	void OnExplode(const FHitResult& SurfaceHit);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ExplodeOverlapObjectTypes;

	FVector Velocity;
};