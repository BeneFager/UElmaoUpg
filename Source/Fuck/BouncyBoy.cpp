// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncyBoy.h"

// Sets default values
ABouncyBoy::ABouncyBoy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABouncyBoy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABouncyBoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

