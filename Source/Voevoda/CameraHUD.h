// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyPlayerCharacter.h"
#include "CameraHUD.generated.h"

UCLASS()
class VOEVODA_API ACameraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	UPROPERTY()
	FVector2D InitialPoint; // position of mouse when pressed
	UPROPERTY()
	FVector2D CurrentPoint; // position of mouse while holding

	UFUNCTION()
	FVector2D GetMousePosition2D();
	
	UPROPERTY()
	bool bStartSelecting = false;
	UPROPERTY()
	TArray <AMyPlayerCharacter*> FoundActors;



};
