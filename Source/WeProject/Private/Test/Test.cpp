// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/Test.h"

#include "GameplayTagsManager.h"

DEFINE_LOG_CATEGORY(WeLog)
// Sets default values
ATest::ATest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATest::BeginPlay()
{
	Super::BeginPlay();
	
}

FGameplayTagContainer ATest::GetGameplayTagsParents(FGameplayTag& GameplayTag)
{
	return UGameplayTagsManager::Get().RequestGameplayTagParents(GameplayTag);
}

void ATest::AddNativeGameplayTag(FName Name)
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(Name);
}

void ATest::PrintAllParentTags(const FGameplayTagContainer& Container)
{
	TArray<FGameplayTag> Result;
	Container.GetGameplayTagArray(Result);
	for(FGameplayTag& Tag:Result)
	{
		UE_LOG(WeLog,Error,TEXT("%s"),*Tag.ToString());
	}
}

void ATest::PrintAllGameplayTags(const FGameplayTagContainer& Container)
{
	
	FGameplayTagContainer Target = Container.GetGameplayTagParents();
	UE_LOG(WeLog,Error,TEXT("%s"),*Target.ToString());
}


// Called every frame
void ATest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void PrintAllParentTags()
{
	
	
}

void PrintAllGameplayTags()
{

	
}
