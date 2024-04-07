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
#include "TerrainType.h"
#include "GameMap.h"
#include "GameWorld.generated.h"

UCLASS()
class MYPROJECT1040_API AGameWorld : public AActor {
    GENERATED_BODY()

public:
    AGameWorld();
    virtual void Tick(float DeltaTime) override;

public:
    virtual void BeginPlay() override;

public:
    void generate_map();
    void OneColorMap();
    void UpdateRhombVision(int32 X, int32 Y, int32 Radius, VisionType vision);

private:
    // UPROPERTY(EditAnywhere, Category = "TileMap")
    UPaperTileMapComponent* TileMapComponent;

    UPaperTileSet* GrassTileSet;
    UPaperTileSet* WaterTileSet;
    UPaperTileSet* MountainsTileSet;
    UPaperTileSet* WoodsTileSet;
    UPaperTileSet* FogTileSet;
    UPaperTileSet* ArmyTileSet;

    UPaperTileSet* DarkGrassTileSet;
    UPaperTileSet* DarkWaterTileSet;

    UPaperTileSet* DarkMountainsTileSet;
    UPaperTileSet* DarkWoodsTileSet;
    GameMap map;
    int32 InitPlayerX;
    int32 InitPlayerY;
    TArray<Army> enemies;
    void ImportTileSets();
    void UpdateTileVision(int32 X, int32 Y, VisionType vision);
};
