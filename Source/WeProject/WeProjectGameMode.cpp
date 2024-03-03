// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeProjectGameMode.h"
#include "WeProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWeProjectGameMode::AWeProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
