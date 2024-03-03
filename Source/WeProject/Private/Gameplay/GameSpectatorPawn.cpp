// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameSpectatorPawn.h"


// Sets default values
AGameSpectatorPawn::AGameSpectatorPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameSpectatorPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameSpectatorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGameSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction(TEXT("ViewNext"),IE_Pressed,this,&AGameSpectatorPawn::ViewNextPlayer);
	InputComponent->BindAction(TEXT("ViewPrev"),IE_Pressed,this,&AGameSpectatorPawn::ViewPrePlayer);
	
}

void AGameSpectatorPawn::ViewNextPlayer()
{
	if(APlayerController* PC = GetController<APlayerController>())
	{
		PC->ServerViewNextPlayer();
	}
}

void AGameSpectatorPawn::ViewPrePlayer()
{
	if(APlayerController* PC = GetController<APlayerController>())
	{
		PC->ServerViewPrevPlayer();
	}
}


