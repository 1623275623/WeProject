// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "GameSpectatorPawn.generated.h"

UCLASS()
class WEPROJECT_API AGameSpectatorPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameSpectatorPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ViewNextPlayer();

	void ViewPrePlayer();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};


