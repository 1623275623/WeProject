// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AbilityInfo.h"

FWeAbilityInfo UAbilityInfo::FindAbilityInTAfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{

	for(const FWeAbilityInfo& Info : AbilityInformation)
	{
		if(Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't find info for abilityTag"));
	}

	return FWeAbilityInfo();
}
