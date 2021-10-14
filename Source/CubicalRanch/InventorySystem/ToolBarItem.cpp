// Fill out your copyright notice in the Description page of Project Settings.

#include "ToolBarItem.h"
#include "UObject/ConstructorHelpers.h"

UToolBarItem::UToolBarItem()
{
	ItemDisplayName = FText::FromString("Empty");
	UseActionText = FText::FromString("");
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("Texture2D'/Game/MyAssets/Icons/Empty.Empty'"));

	if (CrosshiarTexObj.Succeeded())
	{
		Thumbnail = CrosshiarTexObj.Object;
	}

	
}