#include "WeaponPickup.h"
#include "Components/SphereComponent.h"
#include "Fuck/Player/FuckPlayer.h"

AWeaponPickup::AWeaponPickup()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AWeaponPickup::HandleBeginOverlap);
}

void AWeaponPickup::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	auto* Player = Cast<AFuckPlayer>(OtherActor);
	if (Player == nullptr)
		return;

	if (!Player->CanPickupWeaponType(WeaponType))
		return;

	Player->EquipWeapon(WeaponType);
	Destroy();
}

