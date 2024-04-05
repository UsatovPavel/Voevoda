// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Actor.h"
#include "PaperTileLayer.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "Army.h"
#include "MapGenerator.generated.h"
UENUM()
enum TerrainType {
  Grass UMETA(DisplayName = "Grass"),
  Woods UMETA(DisplayName = "Woods"),
  Mountains UMETA(DisplayName = "Mountains"),
  Water UMETA(DisplayName = "Water"),
  Army_position UMETA(DisplayName = "Army position"),
};

UENUM()
enum VisionType {
	Seen UMETA(DisplayName = "Seen"),
  Unseen UMETA(DisplayName = "Unseen"),
};

UCLASS()
class MYPROJECT1040_API AMapGenerator : public AActor {
  GENERATED_BODY()

public:
  AMapGenerator();
  virtual void Tick(float DeltaTime) override;

public:
  virtual void BeginPlay() override;

public:
  void GenerateTileMap();
  void GenerateTerrainData();
  void GenerateEnemies();
  void OneColorMap();
  void UpdateRhombVision(int32 X, int32 Y, int32 Radius, VisionType vision);

private:
  // UPROPERTY(EditAnywhere, Category = "TileMap")
  UPaperTileMapComponent *TileMapComponent;

  UPaperTileSet *GrassTileSet;
  UPaperTileSet *WaterTileSet;
  UPaperTileSet *MountainsTileSet;
  UPaperTileSet *WoodsTileSet;
  UPaperTileSet *FogTileSet;
     UPaperTileSet *ArmyTileSet;

  UPaperTileSet *DarkGrassTileSet;
   UPaperTileSet *DarkWaterTileSet;

      UPaperTileSet *DarkMountainsTileSet;
	   UPaperTileSet *DarkWoodsTileSet;
          int32 MapWidth = 500;
  int32 MapHeight = 300;
  TArray<TArray<TerrainType>> TerrainData;
  int32 InitPlayerX;
  int32 InitPlayerY;
  TArray<Army> enemies;
  void InitTerrainData();
  void ImportTileSets();
  void UpdateTileVision(int32 X, int32 Y, VisionType vision);
};
