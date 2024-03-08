// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeWidgetController.h"
#include "WeGameUIController.generated.h"


class UDataTable;
/**
 * 
 */
UCLASS()
class WEPROJECT_API UWeGameUIController : public UWeWidgetController
{
	GENERATED_BODY()

public:
	//virtual void BroadcastInitialValues() override;
	//virtual void BindCallbacksToDependencies() override;
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	void OnXpChanged(int32 NewXP);

	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
											const FGameplayTag& Slot,const FGameplayTag& PreviousSlot) const;
	



	
};
