// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilityTask_PlayMontageAndWaitEvent.generated.h"


class UGameAbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWePlayMontageAndWaitEventDelegate, FGameplayTag, EventTag, FGameplayEventData,
                                   EventData);


/**
 * 
 */
UCLASS()
class WEPROJECT_API UAbilityTask_PlayMontageAndWaitEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTask_PlayMontageAndWaitEvent(const FObjectInitializer& ObjectInitializer);
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	UPROPERTY(BlueprintAssignable)
	FWePlayMontageAndWaitEventDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FWePlayMontageAndWaitEventDelegate OnBlendOut;

	UPROPERTY(BlueprintAssignable)
	FWePlayMontageAndWaitEventDelegate OnInterrupted;

	
	UPROPERTY(BlueprintAssignable)
	FWePlayMontageAndWaitEventDelegate OnCanceled;

	
	UPROPERTY(BlueprintAssignable)
	FWePlayMontageAndWaitEventDelegate EventReceived;
	
	UFUNCTION(BlueprintCallable,Category="Abilities|Task",meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility",BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_PlayMontageAndWaitEvent* PlayMontageAndWaitEvent(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		FGameplayTagContainer EventTags,
		float Rate = 1.0f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.f
	);


private:
	UPROPERTY()
	UAnimMontage* MontageToPlay;

	UPROPERTY()
	FGameplayTagContainer EventTags;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	float AnimRootMotionTranslationScale;

	UPROPERTY()
	float bStopWhenAbilityEnds;

	bool StopPlayingMontage();

	UGameAbilitySystemComponent* GetTargetASC();

	void OnMontageBlendingOut(UAnimMontage* Montage,bool bInterrupted);
	void OnAbilityCancelled();
	void OnMontageEnded(UAnimMontage* Montage,bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag,const FGameplayEventData* Payload);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle EventHandle;
	FDelegateHandle CancelledHandle;
	
};
