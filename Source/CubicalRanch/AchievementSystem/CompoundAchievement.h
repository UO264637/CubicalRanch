// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AchievementSystem/Achievement.h"
#include "CompoundAchievement.generated.h"

/**
 * 
 */
UCLASS()
class CUBICALRANCH_API UCompoundAchievement : public UAchievement
{
	GENERATED_BODY()

public:
	void Progress(class ACubicalRanchCharacter* Character, int32 Points) override;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UAchievement*> Achievements;

	UPROPERTY(BlueprintReadOnly)
	int32 ActualAchievement;

	UFUNCTION(BlueprintCallable)
	class UAchievement* GetAchievement();

	UFUNCTION(BlueprintCallable)
		TArray<class UAchievement*> GetAchievements();
};
