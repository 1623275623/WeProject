// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/WaitCooldownChance.h"
#include "AbilitySystemComponent.h"
UWaitCooldownChance* UWaitCooldownChance::WaitCooldownChance(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayTag& InCooldownTag)
{
	UWaitCooldownChance* WaitCooldownChance = NewObject<UWaitCooldownChance>();
	WaitCooldownChance->ASC = AbilitySystemComponent;
	WaitCooldownChance->CooldownTag = InCooldownTag;

	if(!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid())
	{
		WaitCooldownChance->EndTask();
		return nullptr;
	}

	AbilitySystemComponent->RegisterGameplayTagEvent(
		InCooldownTag,
		EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCooldownChance,&UWaitCooldownChance::CooldownTagChanged);

	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChance,&UWaitCooldownChance::OnActiveEffectAdded);

	return WaitCooldownChance;

	
	
}

void UWaitCooldownChance::EndTask()
{

	if(!IsValid(ASC)) return;
	ASC->RegisterGameplayTagEvent(CooldownTag,EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	SetReadyToDestroy();
	MarkAsGarbage();
	
}

void UWaitCooldownChance::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if(NewCount == 0)
	{
		CooldownEnd.Broadcast(0.f);
	}
}

void UWaitCooldownChance::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{

	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);

	if(AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
	{
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
		TArray<float> TimesRemaining = ASC->GetActiveEffectsTimeRemaining(GameplayEffectQuery);

		if(TimesRemaining.Num() > 0)
		{
			float TimeRemaining = TimesRemaining[0];
			for(int i = 0; i< TimesRemaining.Num();++i)
			{
				if(TimesRemaining[i] > TimeRemaining)
				{
					TimeRemaining = TimesRemaining[i];
				}
			}

			CooldownStart.Broadcast(TimeRemaining);
			
		}
	}

	
}
