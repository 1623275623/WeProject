// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeAbilitySystemFunctionLibrary.generated.h"

struct FGameplayEffectContextHandle;
/**
 * 
 */
UCLASS()
class WEPROJECT_API UWeAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static bool IsBlockHit(const FGameplayEffectContextHandle& ContextHandle);

	static bool IsCriticalHit(const FGameplayEffectContextHandle& ContextHandle);
};
