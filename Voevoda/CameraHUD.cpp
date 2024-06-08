#include "CameraHUD.h"
// Fill out your copyright notice in the Description page of Project Settings.

//#include "MyPlayerController.h"
#include "GameFramework/PlayerController.h"

void ACameraHUD::DrawHUD()
{
	if (bStartSelecting)
	{
		for (int32 I = 0; I < FoundActors.Num(); I++)
		{
			FoundActors[I]->SetDeselected();
		}
		FoundActors.Empty();
		CurrentPoint = GetMousePosition2D();
		DrawRect(FLinearColor(0, 0, 1, .15f), InitialPoint.X, InitialPoint.Y,
			CurrentPoint.X - InitialPoint.X, CurrentPoint.Y - InitialPoint.Y);
		GetActorsInSelectionRectangle<AMyPlayerCharacter>(InitialPoint, CurrentPoint, FoundActors, false, false);
		
		for (int32 I = 0; I < FoundActors.Num(); I++)
		{
			FoundActors[I]->SetSelected();
		}
	}
}

FVector2D ACameraHUD::GetMousePosition2D()
{
	float PosX = 0;
	float PosY = 0;
	GetOwningPlayerController()->GetMousePosition(PosX, PosY);
	return FVector2D(PosX, PosY);
}