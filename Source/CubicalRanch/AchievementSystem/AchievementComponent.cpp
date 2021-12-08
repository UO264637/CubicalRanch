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

	for (auto& Achievement : Achievements)
	{
		if (Achievement->ID.Equals(ID) && !Achievement->IsAchieved) {
			Achievement->Progress(Character);
		}
	}
}

TArray<class UAchievement*> UAchievementComponent::GetAchievements()
{
	return Achievements;
}
