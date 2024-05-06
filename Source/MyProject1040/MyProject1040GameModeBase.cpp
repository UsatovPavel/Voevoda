// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject1040GameModeBase.h"
#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerCharacter.h"
#include "RTSCameraPawn.h"

AMyProject1040GameModeBase::AMyProject1040GameModeBase() {
  // use our custom PlayerController class
  PlayerControllerClass = AMyPlayerController::StaticClass();

  // Set default pawn class to our character class
  DefaultPawnClass = ARTSCameraPawn::StaticClass();

  // set default pawn class to our Blueprinted character
  // static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrints/BP_MyPlayerCharacter"));
  static ConstructorHelpers::FClassFinder<ARTSCameraPawn> PlayerPawnBPClass(TEXT("/Game/BluePrints/BP_RTSCamera"));
  if (PlayerPawnBPClass.Class != nullptr)
  {
	  DefaultPawnClass = PlayerPawnBPClass.Class;
  }
}