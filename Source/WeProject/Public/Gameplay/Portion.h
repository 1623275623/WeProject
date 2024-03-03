// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Ability/GameGamePlayAbility.h"
#include "Portion.generated.h"
/**
 * 
 */
UCLASS()
class WEPROJECT_API UPortion : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPortion();
	UPROPERTY(EditAnywhere,Category=Attribute)
	FText Name;

	UPROPERTY(EditAnywhere,Category=Attribute)
	FText Description;

	UPROPERTY(EditAnywhere,Category=Attribute)
	int16 Price;
	
	UPROPERTY(EditAnywhere,Category=Attribute)
	FSlateBrush Icon;
	
	UPROPERTY(EditAnywhere,Category=Attribute)
	FPrimaryAssetType Type;

	UPROPERTY(EditDefaultsOnly,Category=Ability)
	TSubclassOf<UGameplayAbility> Ability;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
