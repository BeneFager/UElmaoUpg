// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "MyCharacterMovementComponent.h"

//Set default values
AMyCharacter::AMyCharacter(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
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
}

UMyCharacterMovementComponent* AMyCharacter::GetMyMovementComponent() const
{
	return static_cast<UMyCharacterMovementComponent*>(GetCharacterMovement());
}

