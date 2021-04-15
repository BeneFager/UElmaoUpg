// Copyright Epic Games, Inc. All Rights Reserved.


#include "FuckGameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Player/MyCharacter.h"

AFuckGameModeBase::AFuckGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
}
