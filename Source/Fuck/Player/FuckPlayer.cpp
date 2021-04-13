#include "FuckPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "FuckProjectile.h"
#include "Fuck/Weapon/WeaponBase.h"
#include "Runtime/Engine/Public/TimerManager.h"

AFuckPlayer::AFuckPlayer()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());

	WeaponAttachRoot = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponAttach"));
	WeaponAttachRoot->SetupAttachment(Camera);

	auto* MoveComp = GetCharacterMovement();
	MoveComp->JumpZVelocity = 500.f;
	MoveComp->AirControl = 2.f;

	JumpMaxCount = 2;
	DashStrength = 6000.f;
	DashCooldown = 1.f;
	DashStop = 0.1f;
	CanDash = true;
}

void AFuckPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFuckPlayer::HandleJumpInput);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AFuckPlayer::HandleShootInput);
	PlayerInputComponent->BindAction(TEXT("SwitchWeapon"), IE_Pressed, this, &AFuckPlayer::HandleSwitchWeaponInput);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &AFuckPlayer::HandleDash);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFuckPlayer::HandleMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFuckPlayer::HandleMoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AFuckPlayer::HandleLookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFuckPlayer::HandleLookUp);
}

void AFuckPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AFuckPlayer::EquipWeapon(TSubclassOf<AWeaponBase> Type)
{
	auto* Weapon = GetWorld()->SpawnActor<AWeaponBase>(Type);
	Weapon->PlayerOwner = this;
	Weapon->SetActorHiddenInGame(true);
	Weapons.Add(Weapon);

	Weapon->AttachToComponent(WeaponAttachRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

bool AFuckPlayer::CanPickupWeaponType(TSubclassOf<AWeaponBase> Type)
{
	for (auto* Weapon : Weapons)
	{
		if (Weapon->IsA(Type))
			return false;
	}

	return true;
}

void AFuckPlayer::HandleJumpInput()
{
	Jump();
}

void AFuckPlayer::HandleShootInput()
{
	if (Weapons.Num() == 0)
		return;

	Weapons[CurrentWeaponIdx]->Fire();
}

void AFuckPlayer::HandleSwitchWeaponInput()
{
	if (Weapons.Num() == 0)
		return;

	Weapons[CurrentWeaponIdx]->SetActorHiddenInGame(true);
	CurrentWeaponIdx = (CurrentWeaponIdx + 1) % Weapons.Num();
	Weapons[CurrentWeaponIdx]->SetActorHiddenInGame(false);
}

void AFuckPlayer::HandleDash()
{
	if (CanDash)
	{
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		LaunchCharacter(GetLastMovementInputVector() * DashStrength, true, false);
		CanDash = false;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFuckPlayer::StopDashing, DashStop, false);
	}
}

void AFuckPlayer::StopDashing()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AFuckPlayer::ResetDash, DashCooldown, false);
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
}

void AFuckPlayer::ResetDash()
{
	CanDash = true;
}

void AFuckPlayer::HandleMoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AFuckPlayer::HandleMoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AFuckPlayer::HandleLookRight(float Value)
{
	AddControllerYawInput(Value);
}

void AFuckPlayer::HandleLookUp(float Value)
{
	AddControllerPitchInput(Value);
}
