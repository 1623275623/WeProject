// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEPROJECT_API UWeUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
protected:

	
};
