// Copyright MoxAlehin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Outcome.generated.h"

USTRUCT(BlueprintType)
struct FOutcome
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Outcome")
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Outcome", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
	float Positiveness;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Outcome", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Probability;

	operator FName() const 	{ return Name; }

	operator FString() const { return FString::Printf(TEXT("Name: %s, Positiveness: %f, Probability: %f"), *Name.ToString(), Positiveness, Probability); }

	FOutcome()
		: Name(TEXT("")), Positiveness(0.0f), Probability(0.0f)
	{
	}
};