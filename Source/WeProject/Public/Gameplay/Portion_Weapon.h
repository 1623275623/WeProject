// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Portion.h"
#include "Portion_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class WEPROJECT_API UPortion_Weapon : public UPortion
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly,Category=Weapon)
	AActor* Weapon;

	UPortion_Weapon();
	
};
