// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gameplay/GameHUD.h"
#include "Components/CapsuleComponent.h"
#include "Gameplay/GamePlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponnet");
	
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

UAnimMontage* AGameCharacter::GetHitReactMontage_Implementation()
{
	return ICombatInterface::GetHitReactMontage_Implementation();
}
		
void AGameCharacter::Die(const FVector& DeathImpulse)
{
	
}

FOnDamageSignature& AGameCharacter::GetOnDamageSignature()
{
	return OnDamageSignature;
}

FOnDeathSignature& AGameCharacter::GetOnDeathDelegate()
{
	return DeathSignature;
}

FVector AGameCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& Montaged)
{
	const FGameplayTag& GameplayTags = Montaged;

	
	
	return FVector::One();
}

bool AGameCharacter::IsDead_Implementation()
{
	return ICombatInterface::IsDead_Implementation();
}

AActor* AGameCharacter::GetAvatar_Implementation()
{
	return this;
}


// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	AGameHUD* HUD =Cast<AGameHUD>( UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	HUD->InitGameHUD();


	for(TSubclassOf<UGameplayAbility> Ability:StartupAbilities)
	{
		if(AGamePlayerState* MyPlayerState = Cast<AGamePlayerState>(GetPlayerState()))
		{
			MyPlayerState->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(Ability));
		}
	}
	
}

void AGameCharacter::InitAbilityActorInfo()
{
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

