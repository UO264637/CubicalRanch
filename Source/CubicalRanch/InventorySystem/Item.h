// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class CUBICALRANCH_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	virtual class UWorld* GetWorld() const { return World; }

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class USkeletalMesh* SocketMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 Amount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool IsSelected;

	UFUNCTION(BlueprintImplementableEvent)
	void OnLeftUse(class ACubicalRanchCharacter* Character, FTransform location, AActor* HitActor);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRightUse(class ACubicalRanchCharacter* Character, FTransform location, AActor* HitActor);

	UFUNCTION(BlueprintCallable)
	void Buy(class ACubicalRanchCharacter* Character, int32 Quantity);

	UFUNCTION(BlueprintImplementableEvent)
	void OnBuy(int32 Quantity);

	UFUNCTION(BlueprintCallable)
	void Sell(class ACubicalRanchCharacter* Character, int32 Quantity);
};
