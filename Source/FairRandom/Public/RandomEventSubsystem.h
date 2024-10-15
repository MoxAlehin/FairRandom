// Copyright MoxAlehin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RandomEventDataAsset.h"
#include "RandomEventSubsystem.generated.h"

/** Struct to store information about a random event */
USTRUCT()
struct FRandomEventInfo
{
	GENERATED_BODY()

	/** The data asset associated with this random event */
	UPROPERTY()
	URandomEventDataAsset* EventDataAsset;

	/** Array to store current probabilities or other data */
	UPROPERTY()
	TArray<float> Data;
	
	FRandomEventInfo()
		: EventDataAsset(nullptr)
	{}

	// Serialization function
	friend FArchive& operator<<(FArchive& Ar, FRandomEventInfo& Info)
	{
		Ar << Info.EventDataAsset;
		Ar << Info.Data;
		return Ar;
	}
};

/** Struct to store events for a specific owner */
USTRUCT()
struct FEventData
{
	GENERATED_BODY()

	/** Map of event names to event information */
	UPROPERTY()
	TMap<FName, FRandomEventInfo> Events;

	// Serialization function
	friend FArchive& operator<<(FArchive& Ar, FEventData& Data)
	{
		Ar << Data.Events;
		return Ar;
	}
};

/** Subsystem to manage random events */
UCLASS()
class FAIRRANDOM_API URandomEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    /**
     * Register a random event for an owner
     *
     * @param Owner The object that owns this event
     * @param EventName The name of the event
     * @param EventDataAsset The data asset containing event information
     */
    UFUNCTION(BlueprintCallable, Category = "Math|Random|Events", meta = (Tooltip = "Register a random event for an owner", DefaultToSelf = "Owner"))
    void RegisterEvent(UObject* Owner, FName EventName, URandomEventDataAsset* EventDataAsset);

    /**
     * Unregister a random event for an owner
     *
     * @param Owner The object that owns this event
     * @param EventName The name of the event
     */
    UFUNCTION(BlueprintCallable, Category = "Math|Random|Events", meta = (Tooltip = "Unregister a random event for an owner", DefaultToSelf = "Owner"))
    void UnregisterEvent(UObject* Owner, FName EventName);

	UFUNCTION(BlueprintCallable, Category = "Math|Random|Events", meta = (Tooltip = "Unregister all random events for an owner", DefaultToSelf = "Owner"))
	void UnregisterAllOwnerEvents(UObject* Owner);
	
    /**
     * Clear all registered events
     */
    UFUNCTION(BlueprintCallable, Category = "Math|Random|Events", meta = (Tooltip = "Clear all registered events"))
    void UnregisterAllEvents();

    /**
     * Randomize an event for an owner
     *
     * @param Owner The object that owns this event
     * @param EventName The name of the event
     * @param Luck The luck factor to influence the randomization
     * @param OutOutcome The resulting outcome
     * @param OutIndex The index of the resulting outcome
     */
    UFUNCTION(BlueprintCallable, Category = "Math|Random|Events", meta = (Tooltip = "Randomize an event for an owner", DefaultToSelf = "Owner"))
    void Randomize(UObject* Owner, FName EventName, float Luck, FOutcome& OutOutcome, int32& OutIndex);

    /**
     * Save registered events to a file
     *
     * @param SlotName The name of the save slot
     * @param UserIndex The user index
     */
    UFUNCTION(BlueprintCallable, Category = "Math|Random|Events", meta = (Tooltip = "Save registered events to a file"))
    void SaveEvents(const FString& SlotName = "RandomEvents", const int32 UserIndex = 0) const;

    /**
     * Load registered events from a file
     *
     * @param SlotName The name of the save slot
     * @param UserIndex The user index
     */
    UFUNCTION(BlueprintCallable, Category = "Math|Random|Events", meta = (Tooltip = "Load registered events from a file"))
    void LoadEvents(const FString& SlotName = "RandomEvents", const int32 UserIndex = 0);

private:
    /** Map of owners to their events */
    UPROPERTY()
    TMap<UObject*, FEventData> RegisteredEvents;
};
