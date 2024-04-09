// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter() {
  // Set this character to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  GetCharacterMovement()->GravityScale = 0;

  SpringArmComp =
      CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
  SpringArmComp->SetupAttachment(RootComponent);
  SpringArmComp->TargetArmLength = 180.0f;
  SpringArmComp->bUsePawnControlRotation = false;

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
  Camera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
  Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAxis("MoveForward", this,
                                 &AMyPlayerCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this,
                                 &AMyPlayerCharacter::MoveRight);
}

void AMyPlayerCharacter::MoveForward(float InputValue) {
  position.X = position.X + InputValue * 10;
  SetActorLocation(position);
}

void AMyPlayerCharacter::MoveRight(float InputValue) {
  position.Y = position.Y + InputValue * 10;
  SetActorLocation(position);
}
