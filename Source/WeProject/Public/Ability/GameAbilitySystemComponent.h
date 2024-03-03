// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameAbilitySystemComponent.generated.h"

DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WEPROJECT_API UGameAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameAbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	//Add Startup Gameplay
	void AddStartupGameplayAbilities(TArray<TSubclassOf<UGameplayAbility>> Abilities);

	
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);


	void ForEachAbility(const FForEachAbility& Delegate);
};







