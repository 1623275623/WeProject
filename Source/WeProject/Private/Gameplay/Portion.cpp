// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Portion.h"

UPortion::UPortion()
{
	
}

FPrimaryAssetId UPortion::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(FPrimaryAssetType(TEXT("Portion")),GetFName());
}
