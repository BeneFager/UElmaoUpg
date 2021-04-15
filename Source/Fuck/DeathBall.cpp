#include "DeathBall.h"
#include "Components/BoxComponent.h"
#include "Player/MyCharacter.h"

ADeathBall::ADeathBall()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Sphere"));
	Box->SetBoxExtent(FVector(500.f,500.f,500.f));
	Box->OnComponentBeginOverlap.AddDynamic(this, &ADeathBall::HandleOverlap);

	RootComponent = Box;
}

void ADeathBall::HandleOverlap(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit)
{
	UE_LOG(LogTemp, Log, TEXT("Actor '%s' overlapped"), *OtherActor->GetName());
	auto* lmao = Cast<AMyCharacter>(OtherActor);
	if (lmao)
	{
		lmao->ReturnToStartPos();
	}
}

