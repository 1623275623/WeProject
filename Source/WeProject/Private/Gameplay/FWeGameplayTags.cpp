#include "Gameplay/FWeGameplayTags.h"

#include "GameplayTagsManager.h"

FWeGameplayTags FWeGameplayTags::GameplayTags;
void FWeGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	GameplayTags.AddAllTags(GameplayTagsManager);
	GameplayTagsManager.DoneAddingNativeTags();
}

void FWeGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(InputTag_Move,"InputTag.Move","Move input.");
	AddTag(InputTag_Jump,"InputTag.Jump","Jump input");
	AddTag(InputTag_Jump,"InputTag.Fire","Fire input");
	AddTag(InputTag_Look_Mouse,"InputTag.Look.Mouse","Fire input");
	AddTag(InputTag_Look_Stick,"InputTag.Look,Stick","Fire input");
	

	
}

void FWeGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName),FString(TEXT("(Native)")));
}
