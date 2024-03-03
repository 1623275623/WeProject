// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "WaitCooldownChance.generated.h"

struct FActiveGameplayEffectHandle;
struct FGameplayEffectSpec;
class UAbilitySystemComponent;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCooldownChanceSignature,float,TimeRemaining);




UCLASS(BlueprintType,meta=(ExposedAsyncProxy = "AsyncTask"))
class WEPROJECT_API UWaitCooldownChance : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCooldownChanceSignature CooldownStart;

	UPROPERTY(BlueprintAssignable)
	FCooldownChanceSignature CooldownEnd;

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly=true))
	static UWaitCooldownChance* WaitCooldownChance(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayTag& InCooldownTag);
	
	UFUNCTION(BlueprintCallable)
	void EndTask();


protected:

	TObjectPtr<UAbilitySystemComponent> ASC;
	FGameplayTag CooldownTag;
	

	void CooldownTagChanged(const FGameplayTag InCooldownTag,int32 NewCount);

	void OnActiveEffectAdded(UAbilitySystemComponent* TargetASC,const FGameplayEffectSpec& SpecApplied,FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
};
