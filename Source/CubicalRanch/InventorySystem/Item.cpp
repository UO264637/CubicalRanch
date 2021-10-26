// Fill out your copyright notice in the Description page of Project Settings.


#include "../CubicalRanchCharacter.h"
#include "Item.h"

UItem::UItem()
{
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void UItem::Buy(ACubicalRanchCharacter* Character, int32 Quantity)
{
	if (Character)
	{
		Character->Money -= Quantity * Price;

		Character->GiveItem(this, Quantity);

		OnBuy(Quantity);
	}
}

void UItem::Sell(ACubicalRanchCharacter* Character, int32 Quantity)
{
	if (Character)
	{
		Character->Money += Quantity * Price;

		Character->RemoveItem(this, Quantity);
	}
}
