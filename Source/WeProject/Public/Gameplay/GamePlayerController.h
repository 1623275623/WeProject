// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UDamageTextComponent;
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;
/**
 * 
 */
UCLASS()
class WEPROJECT_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()




public:
	//General Function
	virtual void BeginPlay() override;

	

public:
	

	//Input

	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	

	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> AttackAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere,Category="Skill")
	TObjectPtr<UInputAction> Skill1;

	UPROPERTY(EditAnywhere,Category="Skill")
	TObjectPtr<UInputAction> Skill2;

	UPROPERTY(EditAnywhere,Category="Skill")
	TObjectPtr<UInputAction> Skill3;

	
	UPROPERTY(EditAnywhere,Category="Attack")
	TObjectPtr<UInputAction> CommonAttackAction;

	
	UPROPERTY(EditAnywhere,Category="Attack")
	TObjectPtr<UInputAction> SpecialAttackAction;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> InteractAction;
	
	void Jump() ;

	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);
	
	UFUNCTION(BlueprintNativeEvent)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void SpecialAttack();

	void TriggerSkill1();

	UFUNCTION()
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter,bool bBlockHit,bool bCriticalHit);
	//UPROPERTY()

	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
	
};


