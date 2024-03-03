// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControllableWeapon.generated.h"


class UInputConfig;
class UInputBehavior;
class UInputAction;
struct FInputActionValue;
class UUControllableWeaponMovementComp;
class UControllableMovementComp;
class UCameraComponent;
class UBoxComponent;



UCLASS()
class WEPROJECT_API AControllableWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AControllableWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInput();
public:

	


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UInputConfig* InputConfig;	
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Movement")
	UUControllableWeaponMovementComp* MovementComp;

	UPROPERTY(EditDefaultsOnly, Category="Controllable Weapon")
	UStaticMeshComponent* MeshComponent;
 
	UPROPERTY(EditDefaultsOnly, Category = "Controllable Weapon | Camera")
	UCameraComponent* CameraComponent;
 
	UPROPERTY(EditDefaultsOnly, Category = "Controllable Weapon | Camera")
	UBoxComponent* CollisionBox;

	

 //
	UFUNCTION(BlueprintCallable, Category = "Controllable Weapon | Input")
	void Input_Steer(const FInputActionValue& InputActionValue);
 
	UFUNCTION(BlueprintCallable, Category = "Controllable Weapon | Input")
	void Input_Detonate(const FInputActionValue& InputActionValue);
 
	//Player Controller that controls this actor. Set by owning ability task.
	UPROPERTY(BlueprintReadOnly, Category = "Controllable Weapon")
	APlayerController* PlayerController;
 
	virtual void BecomeViewTarget(APlayerController* PC) override;

	//This is called automatically by the PlayerCameraManager, so we’ll use this as a hook to disable input.
	virtual void EndViewTarget(APlayerController* PC) override;
 
	UFUNCTION()
	void OnControllableWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
 
	//Events	
	DECLARE_EVENT_ThreeParams(AControllableWeapon, FOnExplodeEvent, AControllableWeapon*, AActor*, const FHitResult&);
	FOnExplodeEvent& OnExplodedEvent() { return OnExplodedDelegate; }
 
protected:
 
	FOnExplodeEvent OnExplodedDelegate;
 
	void Explode(AActor* HitActor, const FHitResult& HitResult);
 
	bool bHasExploded;
	
};
