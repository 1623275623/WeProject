// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GamePlayerState.h"
#include "GameAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Gameplay/GameCharacter.h"
#include "Kismet/GameplayStatics.h"

AGamePlayerState::AGamePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AttributeSet = CreateDefaultSubobject<UGameAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGamePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGamePlayerState::AddToXP(int32 AddedXP)
{
	XP += AddedXP;
	OnXpChangedDelegate.Broadcast(XP);
}

void AGamePlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level,true);
}

void AGamePlayerState::AddToAttributePoints(int32 InPoints)
{
	AttributePoints += InPoints;
	OnAttributePointsChanged.Broadcast(InPoints);
}

void AGamePlayerState::AddToSpellPoints(int32 InPoints)
{
	SpellPoints += InPoints;
	OnSpellPointsChanged.Broadcast(InPoints);
}

int32 AGamePlayerState::GetPlayerLevel() const
{
	return Level;
}

int32 AGamePlayerState::GetXP() const
{
	return XP;
}

int32 AGamePlayerState::GetAttributePoints() const
{
	return AttributePoints;
}

int32 AGamePlayerState::GetSpellPoints() const
{
	return SpellPoints;
}

void AGamePlayerState::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this,GetPawn());
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this,&AGamePlayerState::OnHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddUObject(this,&AGamePlayerState::OnManaChanged);
		
	}

	AGameCharacter* MyCharacter = Cast<AGameCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));
	if(MyCharacter)
	{
		MyCharacter->AbilitySystemComponent = AbilitySystemComponent;
	}
}

void AGamePlayerState::OnManaChanged(const FOnAttributeChangeData& Data)
{
	UpdateMana(Data.OldValue,Data.NewValue);
}

float AGamePlayerState::GetMaxHealth() const
{
	if(AttributeSet)
	{
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
	
}

float AGamePlayerState::GetMaxMana() const
{
	if(AttributeSet)
	{
		return AttributeSet->GetMaxMana();
	}
	return 0.0f;
}

void AGamePlayerState::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	UpdateHealth(Data.OldValue,Data.NewValue);
	UE_LOG(LogTemp,Error,TEXT("HealthChanged"));
}
