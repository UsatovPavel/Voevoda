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
#include "Location.h"
#include "TerrainType.h"
#include "CubeTileSetClass.h"
#include "GameMap.h"
#include "Strategist.h"
#include "MyPlayerCharacter.h"
#include "MapPainter.generated.h"

class AGameWorld;
UCLASS()
class VOEVODA_API AMapPainter : public AActor {
    GENERATED_BODY()

public:
    AMapPainter();
    virtual void Tick(float DeltaTime) override;

public:
    virtual void BeginPlay() override;

public:
    void generate_GameMap();
    void generate_TileMap();
    void OneColorMap();
    void UpdateRhombVision(int32 X, int32 Y, int32 Radius, VisionType vision);
    GameMap map;
private:
    // UPROPERTY(EditAnywhere, Category = "TileMap")
    UPaperTileMapComponent* TileMapComponent;

    UPaperTileSet* GrassTileSet;
    UPaperTileSet* WaterTileSet;
    UPaperTileSet* MountainsTileSet;
    UPaperTileSet* WoodsTileSet;
    UPaperTileSet* FogTileSet;
    UPaperTileSet* ArmyTileSet;
    UPaperTileSet* CastleTileSet;

    UPaperTileSet* DarkCastleTileSet;
    UPaperTileSet* DarkGrassTileSet;
    UPaperTileSet* DarkWaterTileSet;
    UPaperTileSet* DarkMountainsTileSet;
    UPaperTileSet* DarkWoodsTileSet;
    int32 InitPlayerX;
    int32 InitPlayerY;

    UPROPERTY(EditAnywhere, Category = "Grid|Setup")
    TSubclassOf<ACubeTileSetClass> CubeTile;
    UPROPERTY(EditAnywhere, Category = "Setup")
        TSubclassOf<AStrategist> StrategistBP;

    TArray<TArray<ACubeTileSetClass*>> Grid2DArray;
    void ImportTileSets();
    void UpdateTileVision(int32 X, int32 Y, VisionType vision);
public:
    AMyPlayerCharacter* player_ptr;
    AGameWorld* GameWorld_ptr;
};
