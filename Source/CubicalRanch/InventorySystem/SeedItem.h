// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Item.h"
#include "SeedItem.generated.h"

/**
 * 
 */
UCLASS()
class CUBICALRANCH_API USeedItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SeedItem")
	TArray<class UStaticMesh*> Stages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SeedItem")
	int32 GrowingDays;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "SeedItem")
	class UItem* Product;

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetStage(int32 Stage);
};