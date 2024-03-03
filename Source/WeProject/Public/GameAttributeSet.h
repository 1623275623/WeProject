// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameAttributeSet.generated.h"

/**
 *	
 */
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){};

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	
	
	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
	
	
};

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class WEPROJECT_API UGameAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	

	UGameAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual auto PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) -> void override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void ShowFloatingText(const FEffectProperties& Props,float Damage,bool bBlockHit,bool bCriticalHit) const;
	
	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,Health)


	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,MaxHealth)

	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,Mana)

	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,MaxMana)


	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,Attack)

	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,Armor)

	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,CriticalChance)

	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,Speed)


	//meta Attribute
	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,Damage)

	UPROPERTY(BlueprintReadOnly,Category="Health")
	FGameplayAttributeData Exp;
	ATTRIBUTE_ACCESSORS(UGameAttributeSet,Exp)


public:

	void HandleInComingDamage(const FEffectProperties& Props);

	void HandleInComingExp(const FEffectProperties& Props);

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Properties);


};
