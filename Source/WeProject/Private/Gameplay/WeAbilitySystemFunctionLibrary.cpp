// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/WeAbilitySystemFunctionLibrary.h"
#
#include "Ability/AbilityTypes.h"

bool UWeAbilitySystemFunctionLibrary::IsBlockHit(const FGameplayEffectContextHandle& ContextHandle)
{
	if(const FWeGameplayEffectContext* EffectContext = static_cast<const FWeGameplayEffectContext*>(ContextHandle.Get()))
	{
		return EffectContext->IsBlockHit();
	}
	return false;
}

bool UWeAbilitySystemFunctionLibrary::IsCriticalHit(const FGameplayEffectContextHandle& ContextHandle)
{
	if(const FWeGameplayEffectContext* EffectContext = static_cast<const FWeGameplayEffectContext*>(ContextHandle.Get()))
	{
		return EffectContext->IsCriticalHit();
	}
	return false;
}

