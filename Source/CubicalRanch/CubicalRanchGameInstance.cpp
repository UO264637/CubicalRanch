// Fill out your copyright notice in the Description page of Project Settings.


#include "CubicalRanchGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

UCubicalRanchGameInstance::UCubicalRanchGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class != NULL)
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}
}

/*void UCubicalRanchGameInstance::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
}*/

void UCubicalRanchGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UCubicalRanchGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UCubicalRanchGameInstance::Start()
{
	//Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (Menu != nullptr)
	{
		//Menu->Teardown();
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	UGameplayStatics::OpenLevel(GetWorld(), "World");

	UE_LOG(LogTemp, Warning, TEXT("Start!"));
}

void UCubicalRanchGameInstance::LoadMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}