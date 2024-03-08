// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeGameUIController.h"

#include "Data/LevelUpInfo.h"
#include "Gameplay/FWeGameplayTags.h"
#include "Gameplay/GamePlayerState.h"


void UWeGameUIController::OnXpChanged(int32 NewXP)
{
	const ULevelUpInfo* LevelUpInfo = GetPS()->LevelUpInfo;
	checkf(LevelUpInfo,TEXT("Unabled to find LevelUpInfo.Please fill out AuraPlayerState Blueprint"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();


	if(Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		
	}
}

void UWeGameUIController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const
{
	const FWeGameplayTags& GameplayTags = FWeGameplayTags::Get();

	FWeAbilityInfo LastSlotInfo;

	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;

	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FWeAbilityInfo Info = AbilityInfo->FindAbilityInTAfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);
}
