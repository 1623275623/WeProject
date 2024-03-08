// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputConfig.h"
#include "WeInputComponent.generated.h"


struct FGameplayTag;
class UInputConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WEPROJECT_API UWeInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;


	template<class UserClass, typename FuncType>
	void BindActionByTag(const UInputConfig* InputConfig,const FGameplayTag& Tag,ETriggerEvent TriggerEvent,UserClass* Object,FuncType Func);
};

template <class UserClass, typename FuncType>
void UWeInputComponent::BindActionByTag(const UInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	checkf(InputConfig,TEXT("666666666666"));
	if(const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA,TriggerEvent,Object,Func);
	}
}
