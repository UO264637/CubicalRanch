// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Achievement.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class CUBICALRANCH_API UAchievement : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Achievement")
	FString ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Achievement")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Achievement", meta = (MultiLine = true))
	FText AchievementName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Achievement", meta = (MultiLine = true))
	FText AchievementDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Achievement")
	bool IsAchieved;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Achievement")
	int32 Advancement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Achievement")
	int32 Step;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Achievement")
	int32 Goal;

	virtual void Progress(class ACubicalRanchCharacter* Character, int32 Points);

	UFUNCTION(BlueprintImplementableEvent)
	void Show(class ACubicalRanchCharacter* Character);
};
