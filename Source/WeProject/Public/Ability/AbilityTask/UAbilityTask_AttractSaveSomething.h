// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UAbilityTask_AttractSaveSomething.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitDelayDelegate);

/**
 * 
 */
UCLASS()
class WEPROJECT_API UUAbilityTask_AttractSaveSomething : public UAbilityTask
{
	GENERATED_BODY()


	UPROPERTY(BlueprintAssignable)
	FWaitDelayDelegate OnFinish;

	virtual void Activate() override;

	virtual FString GetDebugString() const override;

	UFUNCTION(BlueprintCallable,Category="Ability | Tasks",meta=(HidePin = "OwningAbility",DefaultToSelf = "OwningAbility",BlueprintInternalUseOnly="TRUE"))
	static UUAbilityTask_AttractSaveSomething* AttractSaveSomething(UGameplayAbility* OwningAbility,float Time);
	
private:
	void OnTimeFinish();

	float Time;
	float TimeStarted;
	
	

	
};
