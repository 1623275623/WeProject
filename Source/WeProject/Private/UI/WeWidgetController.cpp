// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeWidgetController.h"

#include "GameAttributeSet.h"
#include "Ability/GameAbilitySystemComponent.h"
#include "Gameplay/GamePlayerController.h"
#include "Gameplay/GamePlayerState.h"

DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);


void UWeWidgetController::SetWeWidgetController(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent.Get();
	AttributeSet = WCParams.AttributeSet;
}

void UWeWidgetController::BroadcastInitialValues()
{
}

void UWeWidgetController::BindCallbacksToDependencies()
{
}

void UWeWidgetController::BroadcastAbilityInfo()
{

	

	FForEachAbility BroadcastDelegate;

	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FWeAbilityInfo Info = AbilityInfo->FindAbilityInTAfoForTag(GameAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = GameAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = GameAbilitySystemComponent->GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	GetGameASC()->ForEachAbility(BroadcastDelegate);
	

}

AGamePlayerController* UWeWidgetController::GetPC()
{
	if(GamePlayerController == nullptr)
	{
		GamePlayerController = Cast<AGamePlayerController>(PlayerController);
	}
	return GamePlayerController;
}

AGamePlayerState* UWeWidgetController::GetPS()
{
	if(GamePlayerState == nullptr)
	{
		GamePlayerState = Cast<AGamePlayerState>(PlayerState);
	}
	return GamePlayerState;
}

UGameAbilitySystemComponent* UWeWidgetController::GetGameASC()
{
	if (GameAbilitySystemComponent == nullptr)
	{
		GameAbilitySystemComponent = Cast<UGameAbilitySystemComponent>(GameAbilitySystemComponent);
	}
	return GameAbilitySystemComponent;
}


UGameAttributeSet* UWeWidgetController::GetAS()
{
	if(GameAttributeSet == nullptr)
	{
		GameAttributeSet = Cast<UGameAttributeSet>(AttributeSet);
	}
	return GameAttributeSet;
}
