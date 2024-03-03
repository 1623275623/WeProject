#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

struct FWeGameplayTags
{
public:
	static const FWeGameplayTags& Get()
	{
		return GameplayTags;
	}

	//Input Tags

	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Look_Stick;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Fire;
	
	FGameplayTag Effects_HitReact;
	
	static void InitializeNativeTags();


	
protected:
	void AddAllTags(UGameplayTagsManager& Manager);

	void AddTag(FGameplayTag& OutTag,const ANSICHAR* TagName,const ANSICHAR* TagComment);

private:
	static FWeGameplayTags GameplayTags;
};
