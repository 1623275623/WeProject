// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Test.generated.h"

struct FGameplayTagContainer;
struct FGameplayTag;

WEPROJECT_API DECLARE_LOG_CATEGORY_EXTERN(WeLog,Error,All);


UCLASS()
class WEPROJECT_API ATest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	//Gameplay Tag
	UFUNCTION(BlueprintCallable,Category=GameplayTag)
	FGameplayTagContainer GetGameplayTagsParents(FGameplayTag& GameplayTag);

	UFUNCTION(BlueprintCallable,Category=GameplayTag)
	void AddNativeGameplayTag(FName Name);

	UFUNCTION(BlueprintCallable)
	void PrintAllParentTags(const FGameplayTagContainer& Container);

	UFUNCTION(BlueprintCallable)
	void PrintAllGameplayTags(const FGameplayTagContainer& Container);


	

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
