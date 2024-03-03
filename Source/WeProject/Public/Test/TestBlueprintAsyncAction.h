// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TestBlueprintAsyncAction.generated.h"

/**
 * 
 */
UCLASS()
class WEPROJECT_API UTestBlueprintAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	virtual void Activate() override;

	static UTestBlueprintAsyncAction* TestBlueprintAsyncAction(int32 A,int32 B);


	int32 A;
	int32 B;
	
};
