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
	/** True if the controlled character should navigate to the mouse cursor. */
	//uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	//virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	//void MoveToMouseCursor();

	/** Navigate player to the given world location. */
	//void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	UFUNCTION()
	void SelectionPressed();
	UFUNCTION()
	void SelectionReleased();
	UFUNCTION()
	void MoveReleased();

	UPROPERTY()
	TArray <AMyPlayerCharacter*> SelectedActors;
};
