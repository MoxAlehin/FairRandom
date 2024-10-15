// Copyright MoxAlehin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERandomType : uint8
{
	Pure UMETA(DisplayName = "Pure"),
	Fair UMETA(DisplayName = "Fair"),
	NonRepetitive UMETA(DisplayName = "Non-Repetitive")
};
