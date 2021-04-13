#pragma once
#include "GameFramework/Character.h"
#include "EWallRunSide.h"
#include "FuckPlayer.generated.h"
class AFuckProjectile;
class UCameraComponent;
class AWeaponBase;

UCLASS()
class AFuckPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AFuckPlayer();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* WeaponAttachRoot;

	TArray<AWeaponBase*> Weapons;

	int CurrentWeaponIdx = 0;

	void EquipWeapon(TSubclassOf<AWeaponBase> Type);
	bool CanPickupWeaponType(TSubclassOf<AWeaponBase> Type);

#pragma region dash
	UPROPERTY(EditAnywhere)
	float DashStrength;

	UPROPERTY(EditAnywhere)
	float DashCooldown;

	UPROPERTY(EditAnywhere)
	float DashStop;
#pragma endregion


private:
	void HandleJumpInput();
	void HandleShootInput();
	void HandleSwitchWeaponInput();
	void HandleDash();
	void HandleMoveForward(float Value);
	void HandleMoveRight(float Value);

	void HandleLookRight(float Value);
	void HandleLookUp(float Value);
	void StopDashing();
	void ResetDash();
	FTimerHandle UnusedHandle;
	bool CanDash;
};
