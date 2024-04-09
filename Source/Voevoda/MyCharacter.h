// MyCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class VOEVODA_API AMyCharacter : public ACharacter {
  GENERATED_BODY()

public:
  AMyCharacter();

  virtual void Tick(float DeltaTime) override;

  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

protected:
  virtual void BeginPlay() override;

  void MoveRightOrLeft(float Value);
  void MoveForwardOrBack(float Value);
};
