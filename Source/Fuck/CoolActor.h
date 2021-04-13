#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoolActor.generated.h"

UCLASS()
class FUCK_API ACoolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoolActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

private:
	UPROPERTY(EditAnywhere)
	float Speed = 500.f;

	FVector Velocity;
};
