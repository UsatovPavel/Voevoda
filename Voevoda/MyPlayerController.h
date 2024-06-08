// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraHUD.h"
#include "MyPlayerController.generated.h"

UCLASS()
class AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	
	ACameraHUD* HUDPtr;

protected:
	
	//virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	UFUNCTION()
	void SelectionPressed();
	UFUNCTION()
	void SelectionReleased();
	UFUNCTION()
	void MoveReleased();
	UFUNCTION()
	void  ScoutReleased();

	UPROPERTY()
	TArray <AMyPlayerCharacter*> SelectedActors;
};
