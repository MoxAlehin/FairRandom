// Copyright MoxAlehin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RandomEventSubsystem.h"
#include "RandomEventSaveGame.generated.h"

/**
 * SaveGame class to store random event data
 */
UCLASS()
class FAIRRANDOM_API URandomEventSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	/** Map of owners to their events */
	UPROPERTY()
	TMap<UObject*, FEventData> RegisteredEvents;
};
