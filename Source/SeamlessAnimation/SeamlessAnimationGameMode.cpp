// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeamlessAnimationGameMode.h"
#include "SeamlessAnimationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASeamlessAnimationGameMode::ASeamlessAnimationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/Character_SA_Bp"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
