#pragma once
#include "WeaponBase.h"
#include "AssaultRifle.generated.h"

UCLASS()
class AAssaultRifle : public AWeaponBase
{
	GENERATED_BODY()

public:
	void Fire() override;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETraceTypeQuery> TraceType;
};