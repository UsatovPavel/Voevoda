// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileSet.h"
#include "PaperTileLayer.h"
#include "PaperTileMapComponent.h"
#include  "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "PaperTileMapActor.h"
#include "MapGenerator.generated.h"

UENUM()
enum TerrainType
{
	Grass     UMETA(DisplayName = "Grass"),
	Woods      UMETA(DisplayName = "Woods"),
	Mountains   UMETA(DisplayName = "Mountains"),
	Water   UMETA(DisplayName = "Water"),
};

UCLASS()
class MYPROJECT1040_API AMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	AMapGenerator();
	virtual void Tick(float DeltaTime) override;
public:
	virtual void BeginPlay() override;

public:

	void GenerateTileMap();
	void GenerateTerrainData();
	void OneColorMap();
	void UpdateRhombVision(int32 X, int32 Y, int32 Radius);
private:
	//UPROPERTY(EditAnywhere, Category = "TileMap")
	UPaperTileMapComponent* TileMapComponent;

	UPaperTileSet* GrassTileSet;
	UPaperTileSet* WaterTileSet;
	UPaperTileSet* MountainsTileSet;
	UPaperTileSet* WoodsTileSet;
	UPaperTileSet* FogTileSet;
	int32 MapWidth = 500;
	int32 MapHeight = 300;
	TArray<TArray<TerrainType>> TerrainData;
	int32 InitPlayerX;
	int32 InitPlayerY;

	void InitTerrainData();
	void ImportTileSets();
	void UpdateTileVision(int32 X, int32 Y);
};
