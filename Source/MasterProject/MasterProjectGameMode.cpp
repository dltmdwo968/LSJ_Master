// Copyright Epic Games, Inc. All Rights Reserved.

#include "MasterProjectGameMode.h"
#include "MasterProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMasterProjectGameMode::AMasterProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
