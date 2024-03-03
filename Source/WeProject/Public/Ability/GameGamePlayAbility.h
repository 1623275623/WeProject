// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameGamePlayAbility.generated.h"

/**
 * 
 */
UCLASS()
class WEPROJECT_API UGameGamePlayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameGamePlayAbility();

	// UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category= GameplayEffects)
	// TMap<FGameplayTag,F>
	
	virtual uint8 GetGameplayTaskDefaultPriority() const override;
};
