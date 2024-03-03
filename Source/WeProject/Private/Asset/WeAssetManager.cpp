// Fill out your copyright notice in the Description page of Project Settings.


#include "Asset/WeAssetManager.h"

#include "Gameplay/FWeGameplayTags.h"

UWeAssetManager::UWeAssetManager()
{
}

UWeAssetManager& UWeAssetManager::Get()
{
	check(GEngine);

	UWeAssetManager* MyAssetManager = Cast<UWeAssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void UWeAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FWeGameplayTags::InitializeNativeTags();
}
