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

	if (!ensure(Continue != nullptr)) return false;
	Continue->OnClicked.AddDynamic(this, &UMainMenu::ContinueGame);

	return true;
}

void UMainMenu::StartGame()
{
	OnNewGame();
	Teardown();
}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::ContinueGame()
{
	OnContinueGame();
	Teardown();
}