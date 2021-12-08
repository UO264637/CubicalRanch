// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AchievementComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBICALRANCH_API UAchievementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAchievementComponent();
	
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Achievements")
	TArray<class UAchievement*> Achievements;

	UFUNCTION(BlueprintCallable)
	void ProgressAchievement(class ACubicalRanchCharacter* Character, FString ID);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowAchievement(class UAchievement* Achievement);

	UFUNCTION(BlueprintCallable)
	TArray<class UAchievement*> GetAchievements();
};
