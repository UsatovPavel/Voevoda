// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RTSCameraPawn.generated.h"

UCLASS()
class VOEVODA_API ARTSCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSCameraPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY()
		FVector2D ScreenEdgePadding;
	UPROPERTY(EditAnywhere)
		FVector2D MoveSpeed;
	FVector2D CurrentInputMoveSpeed;

	// Set WASD movement
    void MoveForward(float InputValue);
    void MoveRight(float InputValue);
};
