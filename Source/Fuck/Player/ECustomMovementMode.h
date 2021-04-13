#pragma once

#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_WallRunning UMETA(DisplayName = "Wallrunning"),
	CMOVE_MAX UMETA(Hidden),
};
