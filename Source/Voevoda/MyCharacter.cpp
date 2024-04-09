// MyCharacter.cpp

#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter() {
  PrimaryActorTick.bCanEverTick = true;

  // for Character not to fall
  GetCharacterMovement()->GravityScale = 0;
}

void AMyCharacter::BeginPlay() { Super::BeginPlay(); }

void AMyCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AMyCharacter::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  // Edit Input in Edit, Project settings,Engin input, axis mapping

  PlayerInputComponent->BindAxis("MoveRightOrLeft", this,
                                 &AMyCharacter::MoveRightOrLeft);
  PlayerInputComponent->BindAxis("MoveForwardOrBack", this,
                                 &AMyCharacter::MoveForwardOrBack);
}

void AMyCharacter::MoveRightOrLeft(float Value) {
  if ((Controller != NULL) && (Value != 0.0f)) {

    const FRotator Rotation = Controller->GetControlRotation();
    const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

    AddMovementInput(Direction, Value);
  }
}

void AMyCharacter::MoveForwardOrBack(float Value) {
  if ((Controller != NULL) && (Value != 0.0f)) {
    const FRotator Rotation = Controller->GetControlRotation();
    const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

    AddMovementInput(Direction, Value);
  }
}
// https://github.com/roliveiravictor/games-first-fps/blob/fe1d3806332246605996d903ff541178366525cc/FPSCharacter.cpp
//
