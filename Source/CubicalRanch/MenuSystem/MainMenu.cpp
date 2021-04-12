// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Start != nullptr)) return false;
	Start->OnClicked.AddDynamic(this, &UMainMenu::StartGame);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::StartGame()
{
	//UE_LOG(LogTemp, Warning, TEXT("Start!"));
	if (MenuInterface != nullptr)
	{
		MenuInterface->Start();
	}
}