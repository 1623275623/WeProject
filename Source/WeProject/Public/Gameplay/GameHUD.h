// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class WEPROJECT_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameHUDClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UUserWidget> GameHUD;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> InventoryClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UUserWidget> Inventory;

	UFUNCTION(BlueprintCallable)
	void InitGameHUD();

	
};
