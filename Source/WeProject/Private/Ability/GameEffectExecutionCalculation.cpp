// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GameEffectExecutionCalculation.h"

#include "GameAttributeSet.h"
#include "Ability/FGamePlayEffectContainer.h"

struct FGameDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance);

	FGameDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGameAttributeSet,Attack,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGameAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGameAttributeSet,CriticalChance,Source,false);
		
	}
	
	
};
static const FGameDamageStatics& GameDamageStatics()
{
	static FGameDamageStatics DmgStatics;
	return DmgStatics;
}


void UGameEffectExecutionCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor_Direct():nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor_Direct():nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Attack = 0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GameDamageStatics().AttackDef,EvaluationParameters,Attack);
	Attack = FMath::Max<float>(Attack,0.0);

	float CriticalChance = 0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GameDamageStatics().CriticalChanceDef,EvaluationParameters,CriticalChance);
	CriticalChance = FMath::Max<float>(CriticalChance,0.0);

	float Armor = 0.0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GameDamageStatics().ArmorDef,EvaluationParameters,Armor);
	Attack = FMath::Max<float>(Armor,0.0);

	if(FMath::RandRange(0.,1.)<CriticalChance)
	{
		Attack = Attack * 2.0;
	}
	
	
	
	float DamageDone = Attack - Armor;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GameDamageStatics().ArmorProperty,EGameplayModOp::Additive,DamageDone));
	
	
}
