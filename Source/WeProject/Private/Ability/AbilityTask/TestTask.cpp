// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/AbilityTask/TestTask.h"

UTestTask* UTestTask::TestTask(UGameplayAbility* OwningAbility, int32 A, FString& Name)
{
	UTestTask* MyTask = NewAbilityTask<UTestTask>(OwningAbility);

	MyTask->A = A;
	MyTask->Name = TEXT("Great Me");

	return MyTask;
}

void UTestTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	UE_LOG(LogTemp,Error,TEXT("Tick"));
}

void UTestTask::Activate()
{
	
	Super::Activate();

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0,FColor::Black,FString(TEXT("MyTask is Activate")));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,FTimerDelegate::CreateUObject(this,&UTestTask::OnDestroy,false),5.0,false);
	}
}

void UTestTask::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	UE_LOG(LogTemp,Error,TEXT("The Task is Destoryed"));

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

