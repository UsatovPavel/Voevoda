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
}

void AMyPlayerController::BeginPlay()
{   
	HUDPtr = Cast<ACameraHUD>(GetHUD());
}
/*
void AMyPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AMyPlayerCharacter* MyPawn = Cast<AMyPlayerCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				//SetNewMoveDestination(MyPawn->GetCursorToWorld()->GetComponentLocation());
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}*/
/*
void AMyPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	//MyPawn->SetActorLocation(DestLocation);
	
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
		
		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}*/

void AMyPlayerController::SelectionPressed()
{
	if (HUDPtr)
	{
		HUDPtr->InitialPoint = HUDPtr->GetMousePosition2D();
		HUDPtr->bStartSelecting = true;
	}
	
	// set flag to keep updating destination until released
	//bMoveToMouseCursor = true;
}

void AMyPlayerController::SelectionReleased()
{
	if (HUDPtr)
	{
		HUDPtr->bStartSelecting = false;
		SelectedActors = HUDPtr->FoundActors;
	}
	
	// clear flag to indicate we should stop updating the destination
	//bMoveToMouseCursor = false;
}

void AMyPlayerController::MoveReleased()
{
	for (int32 I = 0; I < SelectedActors.Num(); I++)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		FVector MoveLocation = Hit.Location + FVector(I / 2 * 100, I % 2 * 100, 0);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[I]->GetController(), MoveLocation);
	}
}