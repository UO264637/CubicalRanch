// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBarComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UToolBarComponent::UToolBarComponent()
{
	Size = 8;
}


// Called when the game starts
void UToolBarComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UToolBarComponent::AddItem(UItem* Item)
{
	if (Items.Num() >= Size || !Item)
	{
		return false;
	}

	Items.Add(Item);

	// Update UI
	OnToolBarUpdated.Broadcast();

	return true;
}

bool UToolBarComponent::RemoveItem(UItem* Item)
{
	if (Item)
	{
		Items.RemoveSingle(Item);
		OnToolBarUpdated.Broadcast();
		return true;
	}
	return false;
}

UItem* UToolBarComponent::GetSelected(int32 Position)
{
	return Items[Position];
}

