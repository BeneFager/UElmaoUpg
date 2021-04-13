#include "FuckProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Fuck/Enemy/FuckEnemy.h"
#include "Fuck/Enemy/EnemyHealthComponent.h"
#include "FuckProjectileResponseComponent.h"

AFuckProjectile::AFuckProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AFuckProjectile::BeginPlay()
{
	Super::BeginPlay();
	Velocity = GetActorForwardVector() * 1500.f;
}

void AFuckProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Velocity -= FVector(0.f, 0.f, 980.f) * DeltaTime;

	FHitResult Hit;
	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);

	if (Hit.bBlockingHit)
	{
		OnExplode(Hit);

		TArray<AActor*> OverlappedActors;
		UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), 300.f, ExplodeOverlapObjectTypes, AActor::StaticClass(), TArray<AActor*>(), OverlappedActors);

		for(auto* Actor : OverlappedActors)
		{
			// Get and apply impulses to all primitive components on actor
			TArray<UActorComponent*> Components = Actor->K2_GetComponentsByClass(UPrimitiveComponent::StaticClass());
			for(auto* Component : Components)
			{
				auto* Primitive = Cast<UPrimitiveComponent>(Component);
				Primitive->AddRadialImpulse(GetActorLocation(), 300.f, 200000.f, ERadialImpulseFalloff::RIF_Linear, false);
			}

			auto* HealthComp = Actor->FindComponentByClass<UEnemyHealthComponent>();
			if (HealthComp)
			{
				float Dist = (Actor->GetActorLocation() - GetActorLocation()).Size();
				float DamageScalar = 1.f - FMath::Clamp(Dist / 300.f, 0.f, 1.f);

				HealthComp->TakeDamage(2.f * DamageScalar);
			}
		}

		Destroy();
		return;
	}

	FRotator FacingRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
	SetActorRotation(FacingRotation);
}

void AFuckProjectile::DoVeryCoolThing()
{

}

float AFuckProjectile::GetSuperCoolNumber()
{
	return 3.14;
}

