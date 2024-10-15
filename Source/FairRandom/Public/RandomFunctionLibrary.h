// Copyright MoxAlehin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Outcome.h"
#include "RandomType.h"
#include "RandomFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FAIRRANDOM_API URandomFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Get a random outcome based on the random type
	 *
	 * @param Outcomes The possible outcomes
	 * @param RandomType The type of randomization to use
	 * @param Data The data array to store current probabilities or other information
	 * @param OutOutcome The resulting outcome
	 * @param OutIndex The index of the resulting outcome
	 * @param Luck The luck factor to influence the randomization
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random|Events")
	static void GetRandomOutcome(const TArray<FOutcome>& Outcomes, ERandomType RandomType, UPARAM(ref) TArray<float>& Data, FOutcome& OutOutcome, int32& OutIndex, float Luck);

	/**
	 * Get a pure random outcome
	 *
	 * @param Outcomes The possible outcomes
	 * @param OutOutcome The resulting outcome
	 * @param OutIndex The index of the resulting outcome
	 * @param Luck The luck factor to influence the randomization
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random|Events")
	static void GetPureRandomOutcome(const TArray<FOutcome>& Outcomes, FOutcome& OutOutcome, int32& OutIndex, float Luck);

	/**
	 * Get a non-repetitive random outcome
	 *
	 * @param Outcomes The possible outcomes
	 * @param Data The data array to store current probabilities or other information
	 * @param OutOutcome The resulting outcome
	 * @param OutIndex The index of the resulting outcome
	 * @param Luck The luck factor to influence the randomization
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random|Events")
	static void GetNonRepetitiveRandomOutcome(const TArray<FOutcome>& Outcomes, UPARAM(ref) TArray<float>& Data, FOutcome& OutOutcome, int32& OutIndex, float Luck);
	/**
	 * Get a fair random outcome
	 *
	 * @param Outcomes The possible outcomes
	 * @param Data The data array to store current probabilities or other information
	 * @param OutOutcome The resulting outcome
	 * @param OutIndex The index of the resulting outcome
	 * @param Luck The luck factor to influence the randomization
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random|Events")
	static void GetFairRandomOutcome(const TArray<FOutcome>& Outcomes, UPARAM(ref) TArray<float>& Data, FOutcome& OutOutcome, int32& OutIndex, float Luck);

	/**
	 * Adjust probability with luck factor
	 *
	 * @param Outcome The outcome to adjust
	 * @param Luck The luck factor to apply
	 * @return The adjusted probability
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Random|Events")
	static float AdjustProbabilityWithLuck(const FOutcome& Outcome, float Luck);

	/**
	 * Get random index from segments
	 *
	 * @param Segments The array of segment lengths
	 * @return The index of the chosen segment
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random|Events")
	static int32 GetRandomIndexFromSegments(const TArray<float>& Segments);

	UFUNCTION(BlueprintPure, meta = (ToolTip = "Converts Outcome to String", DisplayName = "Converts Outcome to String", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")
	static FString Conv_OutcomeToString(const FOutcome& Outcome)
	{
		return Outcome;
	}

	UFUNCTION(BlueprintPure, meta = (ToolTip = "Gets Outcome Name", DisplayName = "Gets Outcome Name", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")
	static FName Conv_OutcomeToName(const FOutcome& Outcome)
	{
		return Outcome;
	}
};
