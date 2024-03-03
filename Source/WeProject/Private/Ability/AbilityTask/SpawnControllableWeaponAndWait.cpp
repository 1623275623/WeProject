// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/SpawnControllableWeaponAndWait.h"

#include "Kismet/GameplayStatics.h"

USpawnControllableWeaponAndWait* USpawnControllableWeaponAndWait::SpawnControllableWeaponAndWait(
	UGameplayAbility* OwningAbility, TSubclassOf<AControllableWeapon> Class, const FTransform& SpawnTransform)
{
	USpawnControllableWeaponAndWait* MyObj = NewAbilityTask<USpawnControllableWeaponAndWait>(OwningAbility);
	MyObj->WeaponSpawnTransform = SpawnTransform;

	return MyObj;
}

bool USpawnControllableWeaponAndWait::BeginSpawningActor(UGameplayAbility* OwningAbility,
	TSubclassOf<AControllableWeapon> Class, AControllableWeapon*& SpawnedActor)
{
	SpawnedActor = nullptr;
	if(Ability && Ability->GetCurrentActorInfo()->IsNetAuthority() && ShouldBroadcastAbilityTaskDelegates())
	{
		UWorld* const World = GEngine->GetWorldFromContextObject(OwningAbility,EGetWorldErrorMode::LogAndReturnNull);
		if(World)
		{
			SpawnedActor = World->SpawnActorDeferred<AControllableWeapon>(Class,WeaponSpawnTransform,OwningAbility->GetActorInfo().OwnerActor.Get(),nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			SpawnedActor->OnExplodedEvent().AddUObject(this,&USpawnControllableWeaponAndWait::OnWeaponExploded);
			SpawnedControllableWeapon = SpawnedActor;
		}
	}

	if(SpawnedActor == nullptr)
	{
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			OnFailedToSpawn.Broadcast(FControllableWeaponEventData());
		}
		return false;
	}

	return true;
}

void USpawnControllableWeaponAndWait::FinishSpawningActor(UGameplayAbility* OwningAbility,
	AControllableWeapon* SpawnedActor)
{
	
	if(SpawnedActor)
	{
		SpawnedActor->PlayerController = UGameplayStatics::GetPlayerController(this,0);
		SpawnedActor->FinishSpawning(WeaponSpawnTransform);

		if(IsValid(SpawnedActor) && ShouldBroadcastAbilityTaskDelegates())
		{
			FControllableWeaponEventData ControllableWeaponEventData;
			ControllableWeaponEventData.SpawnedWeapon = Cast<AControllableWeapon>(SpawnedActor);
			OnSpawned.Broadcast(ControllableWeaponEventData);
			
		}
		else
		{
			if(ShouldBroadcastAbilityTaskDelegates())
			{
				OnFailedToSpawn.Broadcast(FControllableWeaponEventData());
			}

			EndTask();
		}
	}
	else
	{
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			OnFailedToSpawn.Broadcast(FControllableWeaponEventData());
		}

		EndTask();
	}
	
}

void USpawnControllableWeaponAndWait::OnWeaponExploded(AControllableWeapon* ControllableWeapon, AActor* HitActor,
	const FHitResult& HitResult)
{
	FControllableWeaponEventData ControllableWeaponEventData;
	ControllableWeaponEventData.SpawnedWeapon = ControllableWeapon;
	ControllableWeaponEventData.HitActor = HitActor;
	ControllableWeaponEventData.HitResult = HitResult;
 
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnExploded.Broadcast(ControllableWeaponEventData);
	}
	
 
	if (Ability != nullptr)
	{
		APlayerController* OwningPlayerController = Ability->GetActorInfo().PlayerController.Get();
 
		if (OwningPlayerController != nullptr)
		{
			OwningPlayerController->PlayerCameraManager->SetViewTarget(OwningPlayerController->GetPawn());
		}
	}
 
	EndTask();
}

void USpawnControllableWeaponAndWait::ExternalCancel()
{
	check(AbilitySystemComponent!= nullptr);
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCanceled.Broadcast(FControllableWeaponEventData());
	}
 
	//Destroy the controllable weapon actor since we've been canceled
	AActor* SpawnedActor = SpawnedControllableWeapon.Get();
	if (SpawnedActor!= nullptr)
	{
		SpawnedActor->Destroy();
	}
 
	Super::ExternalCancel();

}
