// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Gameplay/Actor/ControllableWeapon.h"
#include "SpawnControllableWeaponAndWait.generated.h"


class AControllableWeapon;

USTRUCT(BlueprintType)
struct FControllableWeaponEventData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,Category="Controllable Weapon")
	AControllableWeapon* SpawnedWeapon;

	UPROPERTY(BlueprintReadOnly,Category="Controllable Weapon")
	FHitResult HitResult;

	UPROPERTY(BlueprintReadOnly,Category="Controllable Weapon")
	AActor* HitActor;

	FControllableWeaponEventData()
		:SpawnedWeapon(nullptr)
	{
		
	}
	
};



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnedControllableWeaponEvent,const FControllableWeaponEventData&,ControllableWeaponData);



UCLASS()
class WEPROJECT_API USpawnControllableWeaponAndWait : public UAbilityTask
{
	GENERATED_BODY()


	UPROPERTY(BlueprintAssignable)
	FSpawnedControllableWeaponEvent OnSpawned;

	UPROPERTY(BlueprintAssignable)
	FSpawnedControllableWeaponEvent OnFailedToSpawn;

	UPROPERTY(BlueprintAssignable)
	FSpawnedControllableWeaponEvent OnExploded;

	UPROPERTY(BlueprintAssignable)
	FSpawnedControllableWeaponEvent OnCanceled;

	UFUNCTION(BlueprintCallable,meta=(HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly = "true"))
	static USpawnControllableWeaponAndWait* SpawnControllableWeaponAndWait(UGameplayAbility* OwningAbility,TSubclassOf<AControllableWeapon> Class,const FTransform& SpawnTransform);

	UFUNCTION(BlueprintCallable,meta=(HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly = "true"))
	bool BeginSpawningActor(UGameplayAbility* OwningAbility,TSubclassOf<AControllableWeapon> Class,AControllableWeapon*& SpawnedActor);

	UFUNCTION(BlueprintCallable,meta=(HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly = "true"))
	void FinishSpawningActor(UGameplayAbility* OwningAbility,AControllableWeapon* SpawnedActor);


	
	
	UFUNCTION()
	void OnWeaponExploded(AControllableWeapon* ControllableWeapon,AActor* HitActor,const FHitResult& HitResult);

	virtual void ExternalCancel() override;

protected:

	FTransform WeaponSpawnTransform;
	
	
	UPROPERTY()
	TWeakObjectPtr<AControllableWeapon> SpawnedControllableWeapon;
	
	

	
};
