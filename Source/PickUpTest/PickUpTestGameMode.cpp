// Copyright Epic Games, Inc. All Rights Reserved.

#include "PickUpTestGameMode.h"
#include "PickUpTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

APickUpTestGameMode::APickUpTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
