#include "FuckEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Fuck/Player/FuckProjectileResponseComponent.h"
#include "EnemyHealthComponent.h"

AFuckEnemy::AFuckEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = Sphere;

	HealthComp = CreateDefaultSubobject<UEnemyHealthComponent>(TEXT("HealthComp"));
}

void AFuckEnemy::BeginPlay()
{
	Super::BeginPlay();
	AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	HealthComp->OnDeath.AddDynamic(this, &AFuckEnemy::HandleDeath);
}

void AFuckEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);

	FVector Direction = (Player->GetActorLocation() - GetActorLocation());
	Direction.Normalize();

	AddActorWorldOffset(Direction * Speed * DeltaTime);

	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Direction);
	SetActorRotation(Rotation);
}

void AFuckEnemy::HandleDeath()
{
	Destroy();
}
