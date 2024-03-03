// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Components/UControllableWeaponMovementComp.h"


// Sets default values for this component's properties
UUControllableWeaponMovementComp::UUControllableWeaponMovementComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUControllableWeaponMovementComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUControllableWeaponMovementComp::TickComponent(float DeltaTime, ELevelTick TickType,
                                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUControllableWeaponMovementComp::AddYawInput(float YawDelta)
{
	
	RotationDelta.Yaw +=YawDelta;
	
}

void UUControllableWeaponMovementComp::AddPitchInput(float PitchDelta)
{
	RotationDelta.Pitch += PitchDelta;
}

void UUControllableWeaponMovementComp::AddRollInput(float RollDelta)
{
	RotationDelta.Roll += RollDelta;
}

