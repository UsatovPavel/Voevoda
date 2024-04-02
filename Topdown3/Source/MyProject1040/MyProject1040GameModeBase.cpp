// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject1040GameModeBase.h"

#include "MyCharacter.h"

AMyProject1040GameModeBase::AMyProject1040GameModeBase() {
  // Set default pawn class to our character class
  DefaultPawnClass = AMyCharacter::StaticClass();
}