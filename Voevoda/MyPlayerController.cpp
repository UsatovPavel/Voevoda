// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MyPlayerCharacter.h"
#include "Engine/World.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
/*
void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}*/

void AMyPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AMyPlayerController::SelectionPressed);
	InputComponent->BindAction("LeftMouseClick", IE_Released, this, &AMyPlayerController::SelectionReleased);

	InputComponent->BindAction("RightMouseClick", IE_Released, this, &AMyPlayerController::MoveReleased);
	InputComponent->BindAction("MouseWheel", IE_Released, this, &AMyPlayerController::ScoutReleased);
}

void  AMyPlayerController::ScoutReleased() {

	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	FVector MousePosition = Hit.Location;
	Location MouseLocation(MousePosition);

	for (int32 I = 0; I < SelectedActors.Num(); I++)
	{
		bool  ScoutSend = false;

		for (int32 i = 0; i < SelectedActors[I]->scouts.Num(); i++) {
			if (SelectedActors[I]->scouts[i].active == 0) {
				SelectedActors[I]->scouts[i].execute_scout(MouseLocation);
				ScoutSend = true;
				break;
			}
		}

		SelectedActors[I]->ScoutsWidget->UpdateWidgetSend(ScoutSend);
	}

}

void AMyPlayerController::BeginPlay()
{   
	HUDPtr = Cast<ACameraHUD>(GetHUD());
}

void AMyPlayerController::SelectionPressed()
{
	if (HUDPtr)
	{
		HUDPtr->InitialPoint = HUDPtr->GetMousePosition2D();
		HUDPtr->bStartSelecting = true;
	}
}

void AMyPlayerController::SelectionReleased()
{
	if (HUDPtr)
	{
		HUDPtr->bStartSelecting = false;
		SelectedActors = HUDPtr->FoundActors;
	}
}

void AMyPlayerController::MoveReleased()
{
	// move all selected actors
	for (int32 I = 0; I < SelectedActors.Num(); I++)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		FVector MoveLocation = Hit.Location + FVector(I / 2 * 100, I % 2 * 100, 0);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[I]->GetController(), MoveLocation);
	}
}