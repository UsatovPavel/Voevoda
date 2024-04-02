// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class MYPROJECT1040_API AMyPlayerCharacter : public ACharacter {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  AMyPlayerCharacter();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

protected:
  UPROPERTY(EditAnywhere)
  class UCameraComponent *Camera;
  UPROPERTY(EditAnywhere)
  class USpringArmComponent *SpringArmComp;

  void MoveForward(float InputValue);
  void MoveRight(float InputValue);

public:
  UPROPERTY(EditAnywhere)
  FVector position = FVector(0, 0, 0);
};
