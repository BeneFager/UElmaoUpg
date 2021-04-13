#include "GrenadeLauncher.h"
#include "Fuck/Player/FuckPlayer.h"
#include "Fuck/Player/FuckProjectile.h"
#include "Camera/CameraComponent.h"

void AGrenadeLauncher::Fire()
{
	FTransform SpawnTransform = PlayerOwner->Camera->GetComponentTransform();
	SpawnTransform.AddToTranslation(SpawnTransform.GetRotation().GetForwardVector() * 100.f);

	GetWorld()->SpawnActor<AFuckProjectile>(GrenadeClass, SpawnTransform);
}
