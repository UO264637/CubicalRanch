// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CubicalRanchCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "InventorySystem/Item.h"
#include "InventorySystem/InventoryComponent.h"
#include "InventorySystem/ToolBarComponent.h"
#include "AchievementSystem/AchievementComponent.h"
#include "Engine/World.h"

ACubicalRanchCharacter::ACubicalRanchCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Inventory
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	// ToolBar
	ToolBar = CreateDefaultSubobject<UToolBarComponent>("ToolBar");

	// Money
	Money = 100;

	// Achievements
	Achievements = CreateDefaultSubobject<UAchievementComponent>("Achievements");
}

void ACubicalRanchCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void ACubicalRanchCharacter::UseItem(UItem* Item, bool leftclick, FTransform location, AActor* HitActor)
{
	if (Item)
	{
		if (leftclick)
		{
			Item->OnLeftUse(this, location, HitActor);
		}
		else
		{
			Item->OnRightUse(this, location, HitActor);
		}
	}
}

void ACubicalRanchCharacter::AddItemToToolBar(UItem* Item)
{
	Inventory->RemoveItem(Item);
	ToolBar->AddItem(Item);
}

void ACubicalRanchCharacter::AddItemToInventory(UItem* Item)
{
	ToolBar->RemoveItem(Item);
	Inventory->AddItem(Item);
}

void ACubicalRanchCharacter::GiveItem(UItem* Item, int32 amount)
{
	for (auto& InventoryItem : Inventory->Items)
	{
		if (InventoryItem->ItemDisplayName.ToString() == Item->ItemDisplayName.ToString()) {
			InventoryItem->Amount += amount;
			return;
		}
	}

	for (auto& ToolBarItem : ToolBar->Items)
	{
		if (ToolBarItem->ItemDisplayName.ToString() == Item->ItemDisplayName.ToString()) {
			ToolBarItem->Amount += amount;

			ToolBar->OnToolBarUpdated.Broadcast();
			return;
		}
	}

	Item->Amount = amount;
	Inventory->AddItem(Item);
}

void ACubicalRanchCharacter::RemoveItem(UItem* Item, int32 amount)
{
	for (auto& InventoryItem : Inventory->Items)
	{
		if (InventoryItem->ItemDisplayName.ToString() == Item->ItemDisplayName.ToString()) {
			if (InventoryItem->Amount > amount)
			{
				InventoryItem->Amount -= amount;
			}
			else if (InventoryItem->Amount == amount)
			{
				Inventory->RemoveItem(Item);
			}
			
			Inventory->OnInventoryUpdated.Broadcast();

			return;
		}
	}

	for (auto& ToolBarItem : ToolBar->Items)
	{
		if (ToolBarItem->ItemDisplayName.ToString() == Item->ItemDisplayName.ToString()) {
			if (ToolBarItem->Amount > amount)
			{
				ToolBarItem->Amount -= amount;
			}
			else if (ToolBarItem->Amount == amount)
			{
				ToolBar->RemoveItem(Item);
			}

			ToolBar->OnToolBarUpdated.Broadcast();

			return;
		}
	}
}

TArray<class UItem*> ACubicalRanchCharacter::GetAllItems()
{
	TArray<class UItem*> Items;

	Items.Append(Inventory->Items);
	Items.Append(ToolBar->GetItems());
	
	return Items;
}
