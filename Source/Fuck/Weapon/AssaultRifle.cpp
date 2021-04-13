#include "AssaultRifle.h"
#include "Fuck/Player/FuckPlayer.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Fuck/Enemy/EnemyHealthComponent.h"

void AAssaultRifle::Fire()
{
	FTransform CamTransform = PlayerOwner->Camera->GetComponentTransform();
	FVector Start = CamTransform.GetLocation();
	FVector End = Start + CamTransform.GetRotation().GetForwardVector() * 20000.f;

	FHitResult Hit;
	UKismetSystemLibrary::LineTraceSingle(PlayerOwner, Start, End, TraceType, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, Hit, true);

	if (Hit.bBlockingHit)
	{
		auto* EnemyHealth = Hit.Actor->FindComponentByClass<UEnemyHealthComponent>();
		if (EnemyHealth)
		{
			EnemyHealth->TakeDamage(1.f);
		}
	}
}

