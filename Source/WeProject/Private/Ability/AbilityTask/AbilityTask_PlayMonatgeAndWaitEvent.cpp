// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/AbilityTask_PlayMontageAndWaitEvent.h"
#include "Ability/GameAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"

UAbilityTask_PlayMontageAndWaitEvent::UAbilityTask_PlayMontageAndWaitEvent(const FObjectInitializer& ObjectInitializer)
{
	Rate = 1.0f;

	bStopWhenAbilityEnds = true;
	
}

void UAbilityTask_PlayMontageAndWaitEvent::Activate()
{

	if(Ability == nullptr)
	{
		return;
	}

	bool bPlayMontage = false;
	UGameAbilitySystemComponent* ASC = GetTargetASC();

	if(ASC)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	}
	Super::Activate();
}

void UAbilityTask_PlayMontageAndWaitEvent::ExternalCancel()
{
	Super::ExternalCancel();
}

FString UAbilityTask_PlayMontageAndWaitEvent::GetDebugString() const
{
	return Super::GetDebugString();
}

void UAbilityTask_PlayMontageAndWaitEvent::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

UAbilityTask_PlayMontageAndWaitEvent* UAbilityTask_PlayMontageAndWaitEvent::PlayMontageAndWaitEvent(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay,
	FGameplayTagContainer EventTags, float Rate, FName StartSection, bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale)
{

	UAbilityTask_PlayMontageAndWaitEvent* MyObj = NewAbilityTask<UAbilityTask_PlayMontageAndWaitEvent>(OwningAbility,TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->EventTags = EventTags;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;

	return MyObj;
	
	
}

bool UAbilityTask_PlayMontageAndWaitEvent::StopPlayingMontage()
{
	return false;
}

UGameAbilitySystemComponent* UAbilityTask_PlayMontageAndWaitEvent::GetTargetASC()
{
	return Cast<UGameAbilitySystemComponent>(AbilitySystemComponent);
}

void UAbilityTask_PlayMontageAndWaitEvent::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{

	if(Ability && Ability->GetCurrentMontage() == MontageToPlay)
	{
		AbilitySystemComponent->ClearAnimatingAbility(Ability);
		
	}

	
}

void UAbilityTask_PlayMontageAndWaitEvent::OnAbilityCancelled()
{
}

void UAbilityTask_PlayMontageAndWaitEvent::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}

void UAbilityTask_PlayMontageAndWaitEvent::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
}
