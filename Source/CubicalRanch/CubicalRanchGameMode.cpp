// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CubicalRanchGameMode.h"
#include "CubicalRanchPlayerController.h"
#include "CubicalRanchCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACubicalRanchGameMode::ACubicalRanchGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACubicalRanchPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP_CubicalRanchCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}