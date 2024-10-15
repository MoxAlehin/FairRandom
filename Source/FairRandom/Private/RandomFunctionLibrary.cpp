// Copyright MoxAlehin. All Rights Reserved.

#include "RandomFunctionLibrary.h"

int32 URandomFunctionLibrary::GetRandomIndexFromSegments(const TArray<float>& Segments)
{
	// Calculate the total length of the segments
	float TotalLength = 0.0f;
	for (float Segment : Segments)
	{
		TotalLength += Segment;
	}

	// Get a random point in the total length
	float RandomPoint = FMath::FRand() * TotalLength;

	// Find the segment that contains the random point
	float CumulativeLength = 0.0f;
	for (int32 i = 0; i < Segments.Num(); ++i)
	{
		CumulativeLength += Segments[i];
		if (RandomPoint <= CumulativeLength)
		{
			return i;
		}
	}

	// If no segment is found (which should not happen), return the last index
	return Segments.Num() - 1;
}

float URandomFunctionLibrary::AdjustProbabilityWithLuck(const FOutcome& Outcome, float Luck)
{
	constexpr float Influence = 1.f;
	// Ensure Luck is within the valid range
	Luck = FMath::Clamp(Luck, -1.f, 1.f);

	// Calculate the adjustment factor for the outcome
	//float Positiveness = FMath::Clamp(Outcome.Positiveness, -1.f, 1.f);
	//float Distance = FMath::Abs(Positiveness - Luck);
	//return Outcome.Probability * (1 - MaxInfluence * Distance / 2);
	return Outcome.Probability * FMath::Pow(2, Luck * Outcome.Positiveness * Influence);
}

void URandomFunctionLibrary::GetPureRandomOutcome(const TArray<FOutcome>& Outcomes, FOutcome& OutOutcome, int32& OutIndex, float Luck)
{
	if (Outcomes.Num() == 0)
	{
		OutOutcome = FOutcome();
		OutIndex = -1;
		return;
	}
	TArray<float> AdjustedProbabilities;
	AdjustedProbabilities.Init(0, Outcomes.Num());

	for (int32 i = 0; i < Outcomes.Num(); ++i)
	{
		AdjustedProbabilities[i] = AdjustProbabilityWithLuck(Outcomes[i], Luck);
	}
	
	OutIndex = GetRandomIndexFromSegments(AdjustedProbabilities);
	OutOutcome = Outcomes[OutIndex];
}

void URandomFunctionLibrary::GetNonRepetitiveRandomOutcome(const TArray<FOutcome>& Outcomes, UPARAM(ref) TArray<float>& PreviousResults, FOutcome& OutOutcome, int32& OutIndex, float Luck)
{
	if (Outcomes.Num() == 0)
	{
		OutOutcome = FOutcome();
		OutIndex = -1;
		return;
	}

	// Убедитесь, что PreviousResults имеет правильный размер
	if (PreviousResults.Num() != Outcomes.Num())
	{
		PreviousResults.Init(0.f, Outcomes.Num());
	}

	TArray<float> Pool;
	Pool.SetNumZeroed(Outcomes.Num()); // Убедитесь, что Pool имеет правильный размер
	bool PoolEmpty = true;

	for (int32 i = 0; i < Outcomes.Num(); ++i)
	{
		const float PoolEntity = FMath::Max(0.f, AdjustProbabilityWithLuck(Outcomes[i], Luck) - PreviousResults[i]);
		Pool[i] = PoolEntity;
		if (PoolEntity > 0)
		{
			PoolEmpty = false;
		}
	}

	// Если Pool пуст, сбросьте PreviousResults
	if (PoolEmpty)
	{
		for (int32 i = 0; i < Outcomes.Num(); ++i)
		{
			PreviousResults[i] = 0.f;
			Pool[i] = FMath::Max(0.f, AdjustProbabilityWithLuck(Outcomes[i], Luck));
		}
	}

	OutIndex = GetRandomIndexFromSegments(Pool);
	OutOutcome = Outcomes[OutIndex];
	PreviousResults[OutIndex] = PreviousResults[OutIndex] + 1;
}

void URandomFunctionLibrary::GetFairRandomOutcome(const TArray<FOutcome>& Outcomes, UPARAM(ref) TArray<float>& CurrentProbabilities, FOutcome& OutOutcome, int32& OutIndex, float Luck)
{
    if (Outcomes.Num() == 0)
    {
        OutOutcome = FOutcome();
        OutIndex = -1;
        return;
    }

	if (CurrentProbabilities.Num() != Outcomes.Num())
	{
		CurrentProbabilities.SetNum(Outcomes.Num());
		for (int32 i = 0; i < Outcomes.Num(); ++i)
		{
			CurrentProbabilities[i] = AdjustProbabilityWithLuck(Outcomes[i], Luck);
		}
	}
	
	int32 SelectedIndex = GetRandomIndexFromSegments(CurrentProbabilities);
	
	float Alpha = 1.f;

    // Update the probabilities
    float SelectedProbability = CurrentProbabilities[SelectedIndex];
    CurrentProbabilities[SelectedIndex] = SelectedProbability * (1 - Alpha); // Adjust the influence factor as needed
    float DeltaProbability = SelectedProbability * Alpha; // Adjust the influence factor as needed

    // Calculate squared initial probabilities
    TArray<float> SquaredInitialProbabilities;
	float SumSquaredInitialProbabilities = 0.f;
    for (const FOutcome& Outcome : Outcomes)
    {
	    float Probability = FMath::Square(AdjustProbabilityWithLuck(Outcome, Luck));
    	SquaredInitialProbabilities.Add(Probability);
    	SumSquaredInitialProbabilities += Probability;
    }

    for (int32 i = 0; i < CurrentProbabilities.Num(); ++i)
    {
    	CurrentProbabilities[i] += (SquaredInitialProbabilities[i] / SumSquaredInitialProbabilities) * DeltaProbability;
    }

    OutOutcome = Outcomes[SelectedIndex];
    OutIndex = SelectedIndex;
}

void URandomFunctionLibrary::GetRandomOutcome(const TArray<FOutcome>& Outcomes, ERandomType RandomType, UPARAM(ref) TArray<float>& Data, FOutcome& OutOutcome, int32& OutIndex, float Luck)
{
	switch (RandomType)
	{
	case ERandomType::Pure:
		GetPureRandomOutcome(Outcomes, OutOutcome, OutIndex, Luck);
		break;
	case ERandomType::Fair:
		GetFairRandomOutcome(Outcomes, Data, OutOutcome, OutIndex, Luck);
		break;
	case ERandomType::NonRepetitive:
		GetNonRepetitiveRandomOutcome(Outcomes, Data, OutOutcome, OutIndex, Luck);
		break;
	default:
		OutOutcome = FOutcome();
		OutIndex = -1;
		break;
	}
}