#include "CoolActor.h"

ACoolActor::ACoolActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Mesh->SetupAttachment(RootComponent);

	RootComponent = Mesh;
}

void ACoolActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Hello from CoolActor ;^)"));

	Velocity = GetActorForwardVector() * Speed;
}

void ACoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Velocity -= FVector(0.f, 0.f, 900.f) * DeltaTime;

	FHitResult Hit;
	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);

	if (Hit.bBlockingHit)
	{
		Velocity = FMath::GetReflectionVector(Velocity, Hit.Normal);
		UE_LOG(LogTemp, Log, TEXT("OWIE OWIE OWIE OUCHIE BOBOO"));
	}
}

