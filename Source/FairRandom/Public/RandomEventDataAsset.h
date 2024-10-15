// Copyright MoxAlehin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Outcome.h"
#include "RandomType.h"
#include "RandomEventDataAsset.generated.h"

UCLASS(BlueprintType)
class FAIRRANDOM_API URandomEventDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Random Event")
	TArray<FOutcome> Outcomes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Random Event")
	ERandomType RandomType;
};
