#pragma once

#include "CoreMinimal.h"
#include "MyCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UCameraComponent;


UCLASS(Blueprintable)
class FUCK_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

#pragma region Dashing
	UPROPERTY(EditAnywhere)
	float DashStrength;

	UPROPERTY(EditAnywhere)
	float DashCooldown;

	UPROPERTY(EditAnywhere)
	float DashStop;
#pragma endregion

	FVector startPos;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Movement")
	UMyCharacterMovementComponent* GetMyMovementComponent() const;


	void HandleJumpInput();
	void HandleDash();
	void HandleMoveForward(float Value);
	void HandleMoveRight(float Value);

	void HandleLookRight(float Value);
	void HandleLookUp(float Value);
	void StopDashing();
	void ResetDash();
	void ReturnToStartPos();
	FTimerHandle UnusedHandle;
	bool CanDash;
};
