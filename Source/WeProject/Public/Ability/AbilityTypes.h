#pragma once

#include "GameplayEffectTypes.h"
#include "AbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	float BaseDamage = 0.f;

	UPROPERTY(BlueprintReadWrite)
	int32 AbilityLevel;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag DamageType = FGameplayTag();
	
};


USTRUCT()
struct FWeGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
	bool IsCriticalHit() const
	{
		return bIsCritical;
	}

	bool IsBlockHit() const
	{
		return bIsBlockHit;
	}



	UPROPERTY()
	bool bIsBlockHit = false;
	
	UPROPERTY()
	bool bIsCritical = false;

	// UPROPERTY()
	// bool IsSuccessfulDebuff = false;

	

};
