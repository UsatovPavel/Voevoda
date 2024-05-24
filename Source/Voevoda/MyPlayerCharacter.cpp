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
void AMyPlayerCharacter::BeginPlay() {
    Super::BeginPlay(); 


    for (TActorIterator<AMapPainter> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {
        painter_ptr = Cast<AMapPainter>(*ActorItr);
    }

    //UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
    //APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;

    ////APlayerController* PlayerController = GetController<APlayerController>();

    //if (PlayerController != nullptr)
    //{
    //    SupplyArmyHUD = Cast<ASupplyArmyHUD>(PlayerController->GetHUD());
    //}
    //else {
    //    UE_LOG(LogTemp, Warning, TEXT("PlayerController is nullptr."));
    //}

}

void AMyPlayerCharacter::InitializeStrategist() {
    // Initialize Strategist
    Location init_loc(position.X, position.Y);
    Strategist = NewObject<AStrategist>(this);
    Strategist->id = 0;
    Strategist->general.position = init_loc;
}

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

  position.X = position.X + InputValue*10;
  SetActorLocation(position);

  UpdateMoveX();
}

void AMyPlayerCharacter::MoveRight(float InputValue) {

  position.Y = position.Y + InputValue*10;
  SetActorLocation(position);

  UpdateMoveY();
}

void AMyPlayerCharacter::UpdateMoveX() {
    FVector PlayerLocation = GetWorld()
        ->GetFirstPlayerController()
        ->GetPawn()
        ->GetActorLocation(); // works only from Tick()
    int32 moveX = (static_cast<int>(PlayerLocation.X) - painter_ptr->GetInitPlayerX());
    int32 defaultX = 0; // based on character init coordinates
    int32 Tile_X = abs(
        ((defaultX + moveX) / painter_ptr->GetMapTileWidth()) % painter_ptr->map.Width);
    Strategist->general.position.x = Tile_X;
   /* FString message = FString::Printf(TEXT("x: %d "), Tile_X);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);*/
}
void  AMyPlayerCharacter::UpdateMoveY() {
    FVector PlayerLocation = GetWorld()
        ->GetFirstPlayerController()
        ->GetPawn()
        ->GetActorLocation(); // works only from Tick()
    int32 moveY = (static_cast<int>(PlayerLocation.Y) - painter_ptr->GetInitPlayerY());
    int32 defaultY = 0;
    int32 Tile_Y =
        abs(((defaultY - moveY) / painter_ptr->GetMapTileHeight()) %
            painter_ptr->map.Height); // very easy swap Height and Width
    Strategist->general.position.y = Tile_Y;
    /*FString message = FString::Printf(TEXT("y: %d "), Tile_Y);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);*/

}
