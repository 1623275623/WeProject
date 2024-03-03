// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestBlueprintAsyncAction.h"

void UTestBlueprintAsyncAction::Activate()
{
	Super::Activate();

	
	
}

UTestBlueprintAsyncAction* UTestBlueprintAsyncAction::TestBlueprintAsyncAction(int32 InA, int32 InB)
{
	UTestBlueprintAsyncAction* Task = NewObject<UTestBlueprintAsyncAction> ();
	Task->A = InA;
	Task->B = InB;

	return Task;
}
