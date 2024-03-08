// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "GameCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UGameplayAbility;
class UAttributeSet;
class UGameAttributeSet;
UCLASS(Abstract)
class WEPROJECT_API AGameCharacter : public ACharacter,public ICombatInterface,public IAbilitySystemInterface
{
	GENERATED_BODY()


	//Input
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
public:
	// Sets default values for this character's properties
	AGameCharacter();

	
	//Combat Interface
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual FOnDamageSignature& GetOnDamageSignature() override;
	virtual FOnDeathSignature& GetOnDeathDelegate() override;

	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& Montaged) override;
	
	virtual bool IsDead_Implementation() override;

	virtual AActor* GetAvatar_Implementation() override;

	
	// UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	// void TestFunction(const FGameplayTag& GameplayTag);

	
	FOnDamageSignature OnDamageSignature;
	FOnDeathSignature DeathSignature;
	FOnASCRegistered AscRegistered;



	// //value changed
	//
	// UFUNCTION(BlueprintImplementableEvent)
	// void 
	

	UPROPERTY(BlueprintReadWrite)
	bool bIsStunned = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsShocked = false;
	

	//Called from AttributeSet,
	virtual void HandleDamage(float DamageAmount,const FHitResult& HitInfo,const struct FGameplayTagContainer& DamageTags,AGameCharacter* InstigatorCharacter,AActor* DamageCauser);

	virtual void HandleHealthChanged(float DeltaValue,const FGameplayTagContainer& EventTags);

	virtual void HandleMovementSpeedChanged(float DeltaValue,const FGameplayTagContainer& EventTags);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnDamaged(float DamageAmount,const FHitResult& HitInfo,AGameCharacter* InstigatorCharacter,AActor* DamageCauser);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnHealthChanged(float DeltaValue);
	
	UFUNCTION(BlueprintNativeEvent)
	void OnMoveSpeedChanged(float DeltaValue);

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Weapon)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere,Category=Combat)
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere,Category=Combat)
	FName LeftHandSocketName;
	
	UPROPERTY(EditAnywhere,Category=Combat)
	FName RightHandSocketName;
	
	UPROPERTY(EditAnywhere,Category=Combat)
	FName TailSocketName;



	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;



public:
	UPROPERTY(BlueprintReadOnly)
	bool bDead = false;

	
	UPROPERTY(EditDefaultsOnly,Category="AnimationMontage")
	TObjectPtr<UAnimMontage> CommonAttackMontage;
	

	

	UPROPERTY(EditDefaultsOnly,Category="AnimationMontage")
	TObjectPtr<UAnimMontage> HitReactMontage;

	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UGameAttributeSet> AttributeSet;
	UPROPERTY(EditAnywhere,Category=Abilities)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere,Category=Abilities)
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
