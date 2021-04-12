// Fill out your copyright notice in the Description page of Project Settings.


#include "CubicalRanchGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"

UCubicalRanchGameInstance::UCubicalRanchGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class;
	}
}

void UCubicalRanchGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}

void UCubicalRanchGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	UMainMenu* Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(Menu != nullptr)) return;

	Menu->AddToViewport();
	Menu->bIsFocusable = true;

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;

	Menu->SetMenuInterface(this);
}

void UCubicalRanchGameInstance::Start()
{
	UE_LOG(LogTemp, Warning, TEXT("Start!"));
}
