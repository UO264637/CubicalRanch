// Fill out your copyright notice in the Description page of Project Settings.

#include "Achievement.h"
#include "../CubicalRanchCharacter.h"

void UAchievement::Progress(ACubicalRanchCharacter* Character)
{
	if (Goal != 0)
	{
		if (Advancement < Goal)
		{
			Advancement++;
			if (Advancement % Step == 0 && Advancement != Goal) {
				Show(Character);
			}
		}
		if (Advancement == Goal)
		{
			IsAchieved = true;
			Show(Character);
		}
	}
	else {
		IsAchieved = true;
		Show(Character);
	}
}