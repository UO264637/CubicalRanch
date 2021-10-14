// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToolBarComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToolBarUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBICALRANCH_API UToolBarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UToolBarComponent();

	virtual void BeginPlay() override;

	bool AddItem(class UItem* Item);
	bool RemoveItem(class UItem* Item);

	UFUNCTION(BlueprintCallable)
	UItem* GetSelected();

	UFUNCTION(BlueprintCallable)
	void SetSelected(int32 Index);

	UFUNCTION(BlueprintCallable)
	TArray<class UItem*> GetItems(); 

	UFUNCTION(BlueprintCallable)
	void RemoveStarterItems(); 

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "ToolBar")
	int32 Size;

	UPROPERTY(BlueprintReadOnly, Category = "ToolBar")
	int32 firstEmptySlot;

	UPROPERTY(BlueprintAssignable, Category = "ToolBar")
	FOnToolBarUpdated OnToolBarUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ToolBarItems")
	TArray<class UItem*> Items;
};
