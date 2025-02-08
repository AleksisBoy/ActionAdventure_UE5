// Copyright Epic Games, Inc. All Rights Reserved.

#include "GoingActionGameMode.h"
#include "GoingActionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGoingActionGameMode::AGoingActionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
