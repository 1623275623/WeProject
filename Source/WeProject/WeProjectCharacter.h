// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "WeProjectCharacter.generated.h"

struct FOnAttributeChangeData;
class UGameplayEffect;
class UGameplayAbility;

UCLASS(config=Game)
class AWeProjectCharacter : public ACharacter ,public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category= AbilityComponent,meta=(AllowPrivateAccess="true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;


	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=AbilitySystem,meta=(AllowPrivateAccess = "true"))
	class UGameAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly,Category=AbilitySystem)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly,Category=AbilitySystem)
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;
	
public:
	AWeProjectCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//Called from AttributeSet,
	virtual void HandleDamage(float DamageAmount,const FHitResult& HitInfo,const struct FGameplayTagContainer& DamageTags,AWeProjectCharacter* InstigatorCharacter,AActor* DamageCauser);

	virtual void HandleHealthChanged(float DeltaValue,const FGameplayTagContainer& EventTags);

	virtual void HandleMovementSpeedChanged(float DeltaValue,const FGameplayTagContainer& EventTags);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDamaged(float DamageAmount,const FHitResult& HitInfo,AWeProjectCharacter* InstigatorCharacter,AActor* DamageCauser);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnHealthChanged(float DeltaValue);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnMoveSpeedChanged(float DeltaValue);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void AddStartupGameplayAbilities();

	//Attribute

	float GetHealth() const;

	float GetMaxHealth() const;

	float GetMana() const;

	float GetMaxMana() const;


	
	
	void UpdateHealth(const FOnAttributeChangeData& Data) const;
	void UpdateMana(const FOnAttributeChangeData& Data) const;

	//UI Notify
	UFUNCTION(BlueprintImplementableEvent,Category=UpdateUI)
	void NotifyHealthChanged(float OldValue,float NewValue) const;

	UFUNCTION(BlueprintImplementableEvent,Category=UpdateUI)
	void NotifyManaChanged(float OldValue,float NewValue) const;
};

