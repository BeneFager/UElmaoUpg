#include "MyCharacter.h"
#include "MyCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"


//Set default values
AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());

	auto* MoveComp = GetCharacterMovement();
	MoveComp->JumpZVelocity = 500.f;
	MoveComp->AirControl = 2.f;

	JumpMaxCount = 2;
	DashStrength = 6000.f;
	DashCooldown = 1.f;
	DashStop = 0.1f;
	CanDash = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	startPos = GetActorLocation();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::HandleJumpInput);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &AMyCharacter::HandleDash);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::HandleMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::HandleMoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyCharacter::HandleLookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::HandleLookUp);
}


void AMyCharacter::HandleJumpInput()
{
	Jump();
}

void AMyCharacter::HandleDash()
{
	if (CanDash)
	{
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		LaunchCharacter(GetLastMovementInputVector() * DashStrength, true, false);
		CanDash = false;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyCharacter::StopDashing, DashStop, false);
	}
}

void AMyCharacter::StopDashing()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyCharacter::ResetDash, DashCooldown, false);
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
}

void AMyCharacter::ResetDash()
{
	CanDash = true;
}

void AMyCharacter::ReturnToStartPos()
{
	SetActorLocation(startPos);
}

void AMyCharacter::HandleMoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AMyCharacter::HandleMoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AMyCharacter::HandleLookRight(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::HandleLookUp(float Value)
{
	AddControllerPitchInput(Value);
}

UMyCharacterMovementComponent* AMyCharacter::GetMyMovementComponent() const
{
	return static_cast<UMyCharacterMovementComponent*>(GetCharacterMovement());
}

