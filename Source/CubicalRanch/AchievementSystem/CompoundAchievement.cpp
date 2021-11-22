// Fill out your copyright notice in the Description page of Project Settings.


#include "CompoundAchievement.h"
#include "Achievement.h"

void UCompoundAchievement::Progress(ACubicalRanchCharacter* Character)
{
	Achievements[ActualAchievement]->Progress(Character);

	if (Achievements[ActualAchievement]->IsAchieved && ActualAchievement<Achievements.Num()-1) {
		ActualAchievement++;

		Achievements[ActualAchievement]->Advancement = Achievements[ActualAchievement - 1]->Advancement;
	}
}

UAchievement* UCompoundAchievement::GetAchievement()
{
	return Achievements[ActualAchievement];
}
