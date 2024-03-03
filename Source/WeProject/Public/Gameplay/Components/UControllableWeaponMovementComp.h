// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "UControllableWeaponMovementComp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WEPROJECT_API UUControllableWeaponMovementComp : public UMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUControllableWeaponMovementComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ControllableWeaponMovement")
	float Speed = 500.0f;
 
	UFUNCTION(BlueprintCallable, Category = "ControllableWeaponMovement")
	void AddYawInput(float YawDelta);
 
	UFUNCTION(BlueprintCallable, Category = "ControllableWeaponMovement")
	void AddPitchInput(float PitchDelta);
 
	UFUNCTION(BlueprintCallable, Category = "ControllableWeaponMovement")
	void AddRollInput(float RollDelta);
 
	
	
	
protected:
	FRotator RotationDelta;
	
	
	
};
