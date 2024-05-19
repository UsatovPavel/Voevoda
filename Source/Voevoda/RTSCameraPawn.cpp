// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCameraPawn.h"
#include "MyPlayerController.h"
#include "Engine/GameInstance.h"

// Sets default values
ARTSCameraPawn::ARTSCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = FVector2D(500, 500);
	ScreenEdgePadding = FVector2D(50, 50);
}

// Called when the game starts or when spawned
void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	if (const auto PlayerController = Cast<APlayerController>(Controller)) {
		PlayerController->SetShowMouseCursor(true);
	}
}

// Called every frame
void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// calculate movespeed of the camera
	auto CurrentMoveSpeed = CurrentInputMoveSpeed;
	const auto PlayerController = Cast<APlayerController>(Controller);
	FVector2D MousePosition;
	if (CurrentInputMoveSpeed.X == 0 && CurrentInputMoveSpeed.Y == 0 && PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y)) {
		int32 ViewportWidth = 0, ViewportHeight = 0;
		PlayerController->GetViewportSize(ViewportWidth, ViewportHeight);

		int32 X = 0, Y = 0;
		if (MousePosition.X <= ScreenEdgePadding.X) {
			X = -1;
		}
		if (MousePosition.X >= ViewportWidth - ScreenEdgePadding.X) {
			X = 1;
		}
		if (MousePosition.Y <= ScreenEdgePadding.Y) {
			Y = 1;
		}
		if (MousePosition.Y >= ViewportHeight - ScreenEdgePadding.Y) {
			Y = -1;
		}
			/*
		const auto X = -(MousePosition.X <= ScreenEdgePadding.X) | 
			(MousePosition.X >= ViewportWidth - ScreenEdgePadding.X);
		const auto Y = (MousePosition.Y <= ScreenEdgePadding.Y) |
			-(MousePosition.Y >= ViewportHeight - ScreenEdgePadding.Y);
			*/
		CurrentMoveSpeed = FVector2D(X, Y);
	}

	// move the camera
	auto ForwardVector = FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0);
	ForwardVector.Normalize();

	const auto Forward = ForwardVector * CurrentMoveSpeed.Y * MoveSpeed.Y * DeltaTime;
	const auto Sideways = GetActorRightVector() * CurrentMoveSpeed.X * MoveSpeed.X * DeltaTime;

	const auto NextLocation = GetActorLocation() + Forward + Sideways;
	SetActorLocation(NextLocation);
}

// Called to bind functionality to input
void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this,
		&ARTSCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this,
		&ARTSCameraPawn::MoveRight);
}

void ARTSCameraPawn::MoveForward(float InputValue) {
	auto ForwardVector = FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0);
	ForwardVector.Normalize();

	const auto Forward = ForwardVector * InputValue * 20;

	const auto NextLocation = GetActorLocation() + Forward;
	SetActorLocation(NextLocation);
}

void ARTSCameraPawn::MoveRight(float InputValue) {
	auto ForwardVector = FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0);
	ForwardVector.Normalize();

	const auto Sideways = GetActorRightVector() * InputValue * 20;

	const auto NextLocation = GetActorLocation() + Sideways;
	SetActorLocation(NextLocation);
}
