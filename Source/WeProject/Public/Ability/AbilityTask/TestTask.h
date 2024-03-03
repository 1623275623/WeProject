// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TestTask.generated.h"

/**
 * 
 */
UCLASS()
class WEPROJECT_API UTestTask : public UAbilityTask
{
	GENERATED_BODY()


	static UTestTask* TestTask(UGameplayAbility* OwningAbility,int32 A,FString& Name);

	virtual  void TickTask(float DeltaTime) override;
	
	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

	FTimerHandle TimerHandle;
	int32 A;
	FString Name;
	
};
