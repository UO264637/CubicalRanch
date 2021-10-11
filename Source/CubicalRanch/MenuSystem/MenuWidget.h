// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CUBICALRANCH_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();
	void Teardown();

	UFUNCTION(BlueprintImplementableEvent)
	void OnContinueGame();

	UFUNCTION(BlueprintImplementableEvent)
	void OnNewGame();

protected:
	IMenuInterface* MenuInterface;


};
