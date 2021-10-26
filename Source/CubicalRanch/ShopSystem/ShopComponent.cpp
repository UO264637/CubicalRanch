// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopComponent.h"

// Sets default values for this component's properties
UShopComponent::UShopComponent()
{
	
}

TArray<class UItem*> UShopComponent::GetItems()
{
	return ShopItems;
}
