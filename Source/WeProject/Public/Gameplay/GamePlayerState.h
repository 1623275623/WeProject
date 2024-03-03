// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/PlayerState.h"
#include "GamePlayerState.generated.h"

struct FOnAttributeChangeData;
class UGameAttributeSet;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, int32 /* StatValue*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelChanged,int32 /*StatValue*/,bool /*bLevelUp*/)




class UAttributeSet;
/**
 * 
 */
UCLASS()
class WEPROJECT_API AGamePlayerState : public APlayerState,public  IAbilitySystemInterface
{
	GENERATED_BODY()


public:
	
	AGamePlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	FOnPlayerStateChanged OnXpChangedDelegate;
	FOnLevelChanged OnLevelChangedDelegate;
	FOnPlayerStateChanged OnAttributePointsChanged;
	FOnPlayerStateChanged OnSpellPointsChanged;

	UFUNCTION(BlueprintCallable)
	void AddToXP(int32 AddedXp);
	
	UFUNCTION(BlueprintCallable)
	void AddToLevel(int32 InLevel);

	UFUNCTION(BlueprintCallable)
	void AddToAttributePoints(int32 InPoints);
	
	UFUNCTION(BlueprintCallable)
	void AddToSpellPoints(int32 InPoints);


	UFUNCTION(BlueprintCallable)
	int32 GetPlayerLevel() const;

	
	UFUNCTION(BlueprintCallable)
	int32 GetXP() const;
	

	
	UFUNCTION(BlueprintCallable)
	int32 GetAttributePoints() const;

	
	UFUNCTION(BlueprintCallable)
	int32 GetSpellPoints() const;


	//UI Update
	virtual void BeginPlay() override;

	


	void OnManaChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxMana() const;

	void OnHealthChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealth(float OldValue,float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMana(float OldValue,float NewValue);
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UGameAttributeSet> AttributeSet;
	
	
private:
	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere)
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere)
	int32 SpellPoints;

	UPROPERTY(VisibleAnywhere)
	int32 Gold;

	

	
};
