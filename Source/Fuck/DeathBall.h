#pragma once
#include "GameFramework/Actor.h"
#include "DeathBall.generated.h"
class UBoxComponent;

UCLASS()
class ADeathBall : public AActor
{
	GENERATED_BODY()

public:
	ADeathBall();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Box;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bFromSweep, const FHitResult& SweepHit);
};