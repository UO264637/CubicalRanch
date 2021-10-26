// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShopComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBICALRANCH_API UShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShopComponent();

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> ShopItems;

	UFUNCTION(BlueprintCallable)
	TArray<class UItem*> GetItems();
};
