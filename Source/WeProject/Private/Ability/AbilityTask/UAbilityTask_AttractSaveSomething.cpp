// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/UAbilityTask_AttractSaveSomething.h"

void UUAbilityTask_AttractSaveSomething::Activate()
{
	UWorld* World = GetWorld();
	TimeStarted = World->GetTimeSeconds();

	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle,this,&UUAbilityTask_AttractSaveSomething::OnTimeFinish,Time,false);
}

FString UUAbilityTask_AttractSaveSomething::GetDebugString() const
{
	return Super::GetDebugString();
}

UUAbilityTask_AttractSaveSomething* UUAbilityTask_AttractSaveSomething::AttractSaveSomething(
	UGameplayAbility* OwningAbility, float Time)
{
	UUAbilityTask_AttractSaveSomething* Myobj = NewAbilityTask<UUAbilityTask_AttractSaveSomething>(OwningAbility);

	Myobj->Time = Time;
	return Myobj;
}

void UUAbilityTask_AttractSaveSomething::OnTimeFinish()
{
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		OnFinish.Broadcast();
	}
	EndTask();
}
