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

UCLASS()
class MYPROJECT1040_API AMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	AMapGenerator();

public:
	virtual void BeginPlay() override;

public:

	void GenerateTileMap();

private:
	//UPROPERTY(EditAnywhere, Category = "TileMap")
	UPaperTileMapComponent* TileMapComponent;

	UPaperTileSet* GrassTileSet;
	UPaperTileSet* WaterTileSet;
	UPaperTileSet* MountainsTileSet;
	UPaperTileSet* WoodsTileSet;
	int32 MapWidth = 500;
	int32 MapHeight = 300;

	void ImportTileSets();
};
