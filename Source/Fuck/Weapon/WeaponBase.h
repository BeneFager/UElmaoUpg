#pragma once
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"
class AFuckPlayer;

UCLASS(Abstract)
class AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();
	virtual void Fire() {}
	AFuckPlayer* PlayerOwner;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
};