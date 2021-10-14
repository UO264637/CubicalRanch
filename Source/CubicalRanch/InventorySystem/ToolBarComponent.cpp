// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBarComponent.h"
#include "Item.h"
#include "ToolBarItem.h"

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
		Items.Add(Item);
	}

	firstEmptySlot = Items.Num();

	while (Items.Num() < Size) {
		Items.Add(NewObject<UToolBarItem>());
	}

	Items[0]->IsSelected = true;
}

void UToolBarComponent::RemoveStarterItems()
{
	for (auto& Item : DefaultItems)
	{
		RemoveItem(Item);
	}
}

bool UToolBarComponent::AddItem(UItem* Item)
{
	if (firstEmptySlot >= Size || !Item)
	{
		return false;
	}

	if (Items.Num() == 0)
	{
		Item->IsSelected = true;
	}
	else
	{
		Item->IsSelected = Items[firstEmptySlot]->IsSelected;
	}

	Items[firstEmptySlot] = Item;
	

	firstEmptySlot++;

	// Update UI
	OnToolBarUpdated.Broadcast();

	return true;
}

bool UToolBarComponent::RemoveItem(UItem* Item)
{
	if (Item)
	{
		Items.RemoveSingle(Item);
		Items.Add(NewObject<UToolBarItem>());
		firstEmptySlot--;

		if (Item->IsSelected)
		{
			Items[0]->IsSelected = true;
		}

		OnToolBarUpdated.Broadcast();
		return true;
	}
	return false;
}

UItem* UToolBarComponent::GetSelected()
{
	UItem* selected = NULL; 

	if (Items.Num() > 0) {
		for (auto& Item : Items)
		{
			if (Item->IsSelected) {
				selected = Item; 
			}
		}
	}
	
	return selected;
}

void UToolBarComponent::SetSelected(int32 Index)
{
	GetSelected()->IsSelected = false;
	Items[Index]->IsSelected = true;

	OnToolBarUpdated.Broadcast();
}

TArray<class UItem*> UToolBarComponent::GetItems()
{
	TArray<class UItem*> ItemsToReturn; 

	for (int i = 0; i < firstEmptySlot; i++) { 
		ItemsToReturn.Add(Items[i]); 
	}

	return ItemsToReturn; 
}

