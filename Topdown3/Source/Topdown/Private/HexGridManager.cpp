// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridManager.h"
#include "HexTile.h"

// Sets default values
AHexGridManager::AHexGridManager()
{
	
}

// Called when the game starts or when spawned
void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();
	
	HexGrid2DArray.SetNumZeroed(GridWidth);
	for (int32 I = 0; I < HexGrid2DArray.Num(); I++) {
		HexGrid2DArray[I].SetNumZeroed(GridHeight);
	}

	for (int32 Y = 0; Y < GridHeight; Y++) {
		for (int32 X = 0; X < GridWidth; X++) {
			const bool OddRow = (Y % 2 == 1);
			const float XPos = OddRow ? X * TileHorizontalOffset + OddRowHorizontalOffset : X * TileHorizontalOffset;
			const float YPos = Y * TileVerticalOffset;

			TSubclassOf<AHexTile> TileToSpawn = GrassHexTile;
			if (FMath::RandRange(0.f, 1.f) <= ChanceOfWater) {
				TileToSpawn = WaterHexTile;
			}

			AHexTile* NewTile = GetWorld()->SpawnActor<AHexTile>(TileToSpawn, FVector(FIntPoint(XPos, YPos)), FRotator::ZeroRotator);
			NewTile->TileIndex = FIntPoint(X, Y);
			HexGrid2DArray[X][Y] = NewTile;
		}
	}
}
