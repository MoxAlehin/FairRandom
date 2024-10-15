// Copyright MoxAlehin. All Rights Reserved.

#include "RandomEventSubsystem.h"
#include "RandomFunctionLibrary.h"
#include "RandomEventSaveGame.h"
#include "Kismet/GameplayStatics.h"

void URandomEventSubsystem::RegisterEvent(UObject* Owner, FName EventName, URandomEventDataAsset* EventDataAsset)
{
    if (!Owner || !EventDataAsset) return;

    FRandomEventInfo EventInfo;
    EventInfo.EventDataAsset = EventDataAsset;

    if (EventDataAsset->RandomType == ERandomType::Fair)
    {
        EventInfo.Data.Init(0.f, EventDataAsset->Outcomes.Num());
        for (int32 i = 0; i < EventDataAsset->Outcomes.Num(); ++i)
        {
            EventInfo.Data[i] = EventDataAsset->Outcomes[i].Probability;
        }
    }

    RegisteredEvents.FindOrAdd(Owner).Events.Add(EventName, EventInfo);
}

void URandomEventSubsystem::UnregisterEvent(UObject* Owner, FName EventName)
{
    if (RegisteredEvents.Contains(Owner))
    {
        RegisteredEvents[Owner].Events.Remove(EventName);
        if (RegisteredEvents[Owner].Events.Num() == 0)
        {
            RegisteredEvents.Remove(Owner);
        }
    }
}

void URandomEventSubsystem::UnregisterAllOwnerEvents(UObject* Owner)
{
    if (RegisteredEvents.Contains(Owner))
    {
        RegisteredEvents.Remove(Owner);
    }
}

void URandomEventSubsystem::UnregisterAllEvents()
{
    RegisteredEvents.Empty();
}

void URandomEventSubsystem::Randomize(UObject* Owner, FName EventName, float Luck, FOutcome& OutOutcome, int32& OutIndex)
{
    if (!RegisteredEvents.Contains(Owner)) return;

    FEventData& EventData = RegisteredEvents[Owner];
    if (!EventData.Events.Contains(EventName)) return;

    FRandomEventInfo& EventInfo = EventData.Events[EventName];

    URandomFunctionLibrary::GetRandomOutcome(EventInfo.EventDataAsset->Outcomes, EventInfo.EventDataAsset->RandomType, EventInfo.Data, OutOutcome, OutIndex, Luck);
}

void URandomEventSubsystem::SaveEvents(const FString& SlotName, const int32 UserIndex) const
{
    if (URandomEventSaveGame* SaveGameInstance = Cast<URandomEventSaveGame>(UGameplayStatics::CreateSaveGameObject(URandomEventSaveGame::StaticClass())))
    {
        SaveGameInstance->RegisteredEvents = RegisteredEvents;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, UserIndex);
    }
}

void URandomEventSubsystem::LoadEvents(const FString& SlotName, const int32 UserIndex)
{
    if (const URandomEventSaveGame* LoadGameInstance = Cast<URandomEventSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex)))
    {
        RegisteredEvents = LoadGameInstance->RegisteredEvents;
    }
}