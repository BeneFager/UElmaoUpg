#pragma once
#include "WeaponBase.h"
#include "GrenadeLauncher.generated.h"
class AFuckProjectile;

UCLASS()
class AGrenadeLauncher : public AWeaponBase
{
	GENERATED_BODY()

public:
	void Fire() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFuckProjectile> GrenadeClass;
};
