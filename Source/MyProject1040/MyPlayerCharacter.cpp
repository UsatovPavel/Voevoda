// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter() {
  // Set this character to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  // PrimaryActorTick.bCanEverTick = true;
  // GetCharacterMovement()->GravityScale = 0;

  // Don't rotate character to camera direction
  bUseControllerRotationPitch = false;
  bUseControllerRotationYaw = false;
  bUseControllerRotationRoll = false;

  // Configure character movement
  GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
  GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
  GetCharacterMovement()->bConstrainToPlane = true;
  GetCharacterMovement()->bSnapToPlaneAtStart = true;

  // set SpringArm
  SpringArmComp =
      CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
  SpringArmComp->SetupAttachment(RootComponent);
  SpringArmComp->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
  SpringArmComp->TargetArmLength = 180.0f;
  //SpringArmComp->bUsePawnControlRotation = false;
  SpringArmComp->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
  SpringArmComp->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

  // set Camera
  CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
  CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
  CameraComp->bUsePawnControlRotation = false;

  // Create a decal in the world to show the cursor's location
  CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
  CursorToWorld->SetupAttachment(RootComponent);
  static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/BluePrints/M_Cursor_Decal.M_Cursor_Decal'"));
  if (DecalMaterialAsset.Succeeded())
  {
	  CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
  }
  CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
  CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
  CursorToWorld->SetVisibility(false);

  // Activate ticking in order to update the cursor every frame.
  PrimaryActorTick.bCanEverTick = true;
  PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
// void AMyPlayerCharacter::BeginPlay() { Super::BeginPlay(); }

void AMyPlayerCharacter::SetSelected()
{
	CursorToWorld->SetVisibility(true);
}

void AMyPlayerCharacter::SetDeselected()
{
	CursorToWorld->SetVisibility(false);
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime) { 
    Super::Tick(DeltaTime); 

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = CameraComp->GetComponentLocation();
				FVector EndLocation = CameraComp->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

// Called to bind functionality to input
/*
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
*/