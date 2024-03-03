// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AchievementSystem.generated.h"



/**
 * 
 */
UCLASS()
class WEPROJECT_API UAchievementSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	int32 KillNum;

	int32 Score;

	int32 Gold;



	UFUNCTION()
	void AddScore(int32 InScore);

	UFUNCTION()
	void AddKillNum(int32 InKillNum);

	UFUNCTION()
	void AddGold(int32 InGold);

	
	
	
};
