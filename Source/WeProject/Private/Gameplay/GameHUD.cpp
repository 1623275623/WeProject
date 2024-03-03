// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameHUD.h"
#include "UMG/Public/Blueprint/UserWidget.h"


void AGameHUD::InitGameHUD()
{

	if(GameHUDClass)
	{
		GameHUD = CreateWidget(GetWorld(),GameHUDClass);

		GameHUD->AddToViewport();
		

	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Error"));
	}
	if(InventoryClass)
	{
		Inventory = CreateWidget(GetWorld(),InventoryClass);

		Inventory->AddToViewport();
	}
}
