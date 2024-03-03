// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UControllableWeaponMovementComp.h"
#include "MagicBallMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WEPROJECT_API UMagicBallMovementComponent : public UUControllableWeaponMovementComp
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMagicBallMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Missile")
	float BoostSpeed = 0.0f;
	
};
