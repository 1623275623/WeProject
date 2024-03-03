// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "GameAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "GameAttributeSet.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UGameAttributeSet>("AttributeSet");

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	


	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	for(TSubclassOf<UGameplayAbility> Ability:StartupAbilities)
	{
		AbilitySystemComponent->GiveAbility(Ability);
	}


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this,&AEnemyBase::UpdateHealth);
}


// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

void AEnemyBase::Die(const FVector& DeathImpulse)
{
	Super::Die(DeathImpulse);

	SpawnLoot();
	
	
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyBase::UpdateHealth(const FOnAttributeChangeData& Data)
{
	UpdateHealthUI(Data.OldValue,Data.NewValue);
}

float AEnemyBase::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}



