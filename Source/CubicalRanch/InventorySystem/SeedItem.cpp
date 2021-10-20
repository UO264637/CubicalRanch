// Fill out your copyright notice in the Description page of Project Settings.


#include "SeedItem.h"
#include "CubicalRanchCharacter.h"


UStaticMesh* USeedItem::GetStage(int32 Stage)
{
	if (Stage >= GrowingDays)
	{
		Stage = GrowingDays - 1;
	}

	int32 StageToReturn = Stage * Stages.Num() / GrowingDays;

	if (StageToReturn == Stages.Num() && Stage < GrowingDays-1)
	{
		StageToReturn--;
	}

	return Stages[StageToReturn];
}
