// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndOfEverfallGameMode.h"
#include "EndOfEverfallHUD.h"
#include "EndOfEverfallCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndOfEverfallGameMode::AEndOfEverfallGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEndOfEverfallHUD::StaticClass();
}
