#pragma once
#include "Components/ActorComponent.h"
#include "FuckProjectileResponseComponent.generated.h"

class AFuckProjectile;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFuckProjectileOnHitEvent, AFuckProjectile*, Projectile);

UCLASS(Meta = (BlueprintSpawnableComponent))
class UFuckProjectileResponseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFuckProjectileResponseComponent();

	UPROPERTY(BlueprintAssignable)
	FFuckProjectileOnHitEvent OnProjectileHit;
};