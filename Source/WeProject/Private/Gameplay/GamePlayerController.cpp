// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GamePlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Gameplay/GamePlayerState.h"
#include "Gameplay/Components/DamageTextComponent.h"
#include "PhysicsProxy/GeometryCollectionPhysicsProxy.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AGamePlayerController::Jump()
{
	
	if (GetCharacter() && GetCharacter()->CanJump())
	{
		GetCharacter()->Jump();
	}
}

void AGamePlayerController::Move(const FInputActionValue& InputActionValue)
{
	
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);  
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	

	if(GetPawn())
	{
		GetPawn()->AddMovementInput(RightDirection,InputAxisVector.X);
		GetPawn()->AddMovementInput(ForwardDirection,InputAxisVector.Y);
	}
	
}

void AGamePlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D Input = InputActionValue.Get<FVector2D>();

	AddYawInput(Input.X);
	AddPitchInput(Input.Y);

}

void AGamePlayerController::SpecialAttack()
{
	
}


void AGamePlayerController::TriggerSkill1()
{
}

void AGamePlayerController::ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockHit,
	bool bCriticalHit)
{
	if(IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount,bBlockHit,bCriticalHit);
	}
}

void AGamePlayerController::Attack_Implementation()
{
	if(AGamePlayerState* State = GetPlayerState<AGamePlayerState>())
	{
		FGameplayTagContainer TagContainer;
		//TagContainer.AddTag(&FGameplayTag(TEXT("BasicSkill.Attack")));
		
		
	}
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
	if(UEnhancedInputComponent* MyInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		MyInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&AGamePlayerController::Jump);
		MyInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AGamePlayerController::Move);
		MyInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AGamePlayerController::Look);
		MyInputComponent->BindAction(CommonAttackAction,ETriggerEvent::Triggered,this,&AGamePlayerController::Attack);
		

	}
	
}
