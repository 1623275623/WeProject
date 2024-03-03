// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "WeAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class WEPROJECT_API UWeAssetManager : public UAssetManager
{
	GENERATED_BODY()


public:
	UWeAssetManager();


	static UWeAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
