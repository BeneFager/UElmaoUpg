#include "DeathBall.h"
#include "Components/SphereComponent.h"

ADeathBall::ADeathBall()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSphereRadius(500.f);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADeathBall::HandleOverlap);

	RootComponent = Sphere;
}

void ADeathBall::HandleOverlap(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	UE_LOG(LogTemp, Log, TEXT("Actor '%s' overlapped"), *OtherActor->GetName());
	OtherActor->Destroy();
}

