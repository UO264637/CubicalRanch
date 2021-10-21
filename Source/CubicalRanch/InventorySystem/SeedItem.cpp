// Fill out your copyright notice in the Description page of Project Settings.


#include "SeedItem.h"
#include "CubicalRanchCharacter.h"


UStaticMesh* USeedItem::GetStage(int32 Stage)
{
	if (Stage > GrowingDays)
	{
		Stage = GrowingDays;
	}
	
	int32 StageToReturn = Stage * Stages.Num() / GrowingDays;

	if (StageToReturn >= Stages.Num()-1 && Stage <= GrowingDays)
	{
		StageToReturn--;
	}

	return Stages[StageToReturn];
}
