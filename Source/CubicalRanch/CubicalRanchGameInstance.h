// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "CubicalRanchGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CUBICALRANCH_API UCubicalRanchGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UCubicalRanchGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void Start();

private:
	TSubclassOf<class UUserWidget> MenuClass;

	class UMainMenu* Menu;
};
