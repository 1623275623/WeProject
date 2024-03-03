// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "GameplayEffectTypes.h"
#include "EnemyBase.generated.h"

class AEnemyAIController;
class UBehaviorTree;
class UWidgetComponent;

UCLASS(BlueprintType)
class WEPROJECT_API AEnemyBase : public AGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitAbilityActorInfo() override;
	
	virtual void Die(const FVector& DeathImpulse) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateHealth(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthUI(float OldValue,float NewValue);
	
	
	UPROPERTY(BlueprintReadWrite,Category="Combat")
	TObjectPtr<AActor> CombatTarget;
	

	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere,Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AEnemyAIController> AIController;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnLoot();

	//Update Health

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;
	
	
};
