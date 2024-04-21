// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
UENUM()
enum TerrainType {
    Grass UMETA(DisplayName = "Grass"),
    Woods UMETA(DisplayName = "Woods"),
    Mountains UMETA(DisplayName = "Mountains"),
    Water UMETA(DisplayName = "Water"),
    Army_position UMETA(DisplayName = "Army position"),
    Castle UMETA(DisplayName = "Castle"),
     //City UMETA(DisplayName = "City"),
    Empty UMETA(DisplayName = "Empty"),
};

UENUM()
enum VisionType {
	Seen UMETA(DisplayName = "Seen"),
  Unseen UMETA(DisplayName = "Unseen"),
};