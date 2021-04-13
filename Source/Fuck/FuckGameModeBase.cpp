// Copyright Epic Games, Inc. All Rights Reserved.


#include "FuckGameModeBase.h"
#include "Player/FuckPlayer.h"

AFuckGameModeBase::AFuckGameModeBase()
{
	DefaultPawnClass = AFuckPlayer::StaticClass();
}
