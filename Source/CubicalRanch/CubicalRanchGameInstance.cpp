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

	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UCubicalRanchGameInstance::Start()
{
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/TopDownCPP/Maps/TopDownExampleMap?listen");

	UE_LOG(LogTemp, Warning, TEXT("Start!"));
}
