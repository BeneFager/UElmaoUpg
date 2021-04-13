#pragma once
#include "GameFramework/Actor.h"
#include "WeaponPickup.generated.h"
class USphereComponent;
class AWeaponBase;

UCLASS()
class AWeaponPickup : public AActor
{
	GENERATED_BODY()

public:
	AWeaponPickup();

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditInstanceOnly)
	TSubclassOf<AWeaponBase> WeaponType;
};