// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Start != nullptr)) return false;
	Start->OnClicked.AddDynamic(this, &UMainMenu::StartGame);

	if (!ensure(Quit != nullptr)) return false;
	Quit->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

	return true;
}

void UMainMenu::StartGame()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Start();
		Teardown();
	}
}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}