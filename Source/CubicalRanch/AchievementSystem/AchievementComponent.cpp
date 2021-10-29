// Fill out your copyright notice in the Description page of Project Settings.

#include "Achievement.h"
#include "AchievementComponent.h"
#include "../CubicalRanchCharacter.h"

// Sets default values for this component's properties
UAchievementComponent::UAchievementComponent()
{

}

void UAchievementComponent::ProgressAchievement(ACubicalRanchCharacter* Character, FString ID)
{
	UE_LOG(LogTemp, Warning, TEXT("Progress!"));

	for (auto& Achievement : Achievements)
	{
		if (Achievement->ID.Equals(ID) && !Achievement->IsAchieved) {
			UE_LOG(LogTemp, Warning, TEXT("A"));
			Achievement->Progress(Character);
		}
	}
}
