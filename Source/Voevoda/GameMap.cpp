// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"
//#define DEBUG_ONE_AI
GameMap::GameMap() {
    Height = FMath::RandRange(50, 80);
    Width = FMath::RandRange(50, 80);
    TArray<TerrainType> DefaultStrip;
    DefaultStrip.Init(Grass, Height);
    TerrainData.Init(DefaultStrip, Width);
}
void GameMap::random_generate()
{
    for (int32 X = 0; X < Width; ++X) {
        for (int32 Y = 0; Y < Height; ++Y) {
            int32 Scale1 = X;
            int32 Scale2 = Y;
            float NoiseValue =
                FMath::PerlinNoise2D(FVector2D(Scale1 / 15.0f, Scale2 / 15.0f));
            NoiseValue = (NoiseValue + 1.0f) / 2.0f;
            if (NoiseValue < 0.2f) {
                TerrainData[X][Y] = Mountains;
            }
            else if (NoiseValue < 0.25f) {
                TerrainData[X][Y] = Grass;
            }
            else if (NoiseValue < 0.35f) {
                TerrainData[X][Y] = Woods;
            }
            else if (NoiseValue < 0.45f) {
                TerrainData[X][Y] = Grass;
            }
            else if (NoiseValue < 0.50f) {
                TerrainData[X][Y] = Water;
            }
            else {
                TerrainData[X][Y] = Grass;
            }
        }
    }
}


void GameMap::random_woods_and_mountains() {

	int32 SeedForMountains_X = FMath::RandRange(0, 300);
	int32 SeedForMountains_Y = FMath::RandRange(0, 300);

	int32 SeedForWoods_X = FMath::RandRange(0, 300);
	int32 SeedForWoods_Y = FMath::RandRange(0, 300);

	FString message2 = FString::Printf(TEXT("SeedForWoods_X: %d, SeedForWoods_X: %d"), SeedForWoods_X, SeedForWoods_X);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message2);

	for (int32 X = 0; X < Width; ++X) {
		for (int32 Y = 0; Y < Height; ++Y) {

			int32 ScaleForMountains1 = X + SeedForMountains_X;
			int32 ScaleForMountains2 = Y + SeedForMountains_Y;

			float NoiseValueForMountains =
				FMath::PerlinNoise2D(FVector2D(ScaleForMountains1 / 15.0f, ScaleForMountains2 / 15.0f));
			NoiseValueForMountains = (NoiseValueForMountains + 1.0f) / 2.0f;


			int32 ScaleForWoods1 = X + SeedForWoods_X;
			int32 ScaleForWoods2 = Y + SeedForWoods_Y;

			float NoiseValueForWoods =
				FMath::PerlinNoise2D(FVector2D(ScaleForWoods1 / 15.0f, ScaleForWoods2 / 15.0f));
			NoiseValueForWoods = (NoiseValueForWoods + 1.0f) / 2.0f;

			if (NoiseValueForMountains < 0.25f) {
				TerrainData[X][Y] = Mountains;
			}
			if (NoiseValueForWoods > 0.75f) {
				TerrainData[X][Y] = Woods;
				//grassTiles.Add(FIntPoint(X, Y));
			}
			else  {
				TerrainData[X][Y] = Grass;
			}
		}
	}

}


void GameMap::random_river() {

	for (size_t count = 0; count < Width/20; count++)
	{

		int32 StartX = FMath::RandRange(10, Width - 10);
		int32 StartY = FMath::RandRange(10, Height - 10);

		int32 HeadwaterWidth = FMath::RandRange(3, 7);

		for (int32 i = 1; i <= HeadwaterWidth; i++)
		{
			for (int32 j = 0; j < i; j++)
			{
				TerrainData[StartX - i + 1 + j][StartY + i - 1] = Water;
			}
		}

		TArray<int32> DirectionX = {1,1,1, 1, 1, 1 ,1, 0, 1, 1, 1, 0, 1, -1, -1, 0 };
		TArray<int32> DirectionY = {1,1,0,-1, 1, 1 ,0, 1, 1, 1, 0, 1, -1, 1, 0, -1 };

		while (StartX != 0 && StartY != 0 && StartX != Width - 1 && StartY != Height - 1) {

			int32 Direction = FMath::RandRange(0, DirectionY.Num() - 1);

			StartX += DirectionX[Direction];
			StartY += DirectionY[Direction];

			if (TerrainData[StartX][StartY] != Water && TerrainData[StartX][StartY] != Grass) {
				break;
			}

			TerrainData[StartX][StartY] = Water;

		}

	}


}

void GameMap::generate_enemies() {
    float x = Width * Height / 300;//one Army_position for 33^2 tiles

#ifdef DEBUG_ONE_AI
    GeneralsInitPos.Add({ 5, 5 });
    x = 0;
#endif
    int32 enemies_count = x * FMath::RandRange(10, 15) / 10;
    for (int32 enemy_ind = 0; enemy_ind < enemies_count; enemy_ind++) {
        while (true) {
            int32 X = FMath::RandRange(0, Width - 1);
            int32 Y = FMath::RandRange(0, Height - 1);
            if (TerrainData[X][Y] == Grass) {
                TerrainData[X][Y] = Army_position;
                GeneralsInitPos.Add({ X, Y });//Add<=>push_back
                break;
            }
        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("From Map size %lld"), GeneralsInitPos.Num()));
}
void GameMap::generate_castles() {
    float x = Width * Height / 100;//one Castle for 33^2 tiles
    int32 enemies_count = x * FMath::RandRange(10, 15) / 10;
    for (int32 enemy_ind = 0; enemy_ind < enemies_count; enemy_ind++) {
        while (true) {
            int32 X = FMath::RandRange(0, Width - 1);
            int32 Y = FMath::RandRange(0, Height - 1);
            if (TerrainData[X][Y] == Grass) {
                TerrainData[X][Y] = Castle;
                CastlesInitPos.Add({ X, Y });//Add<=>push_back
                break;
            }
        }
    }
}
TerrainType GameMap::get_terrain(Location loc) const {
    if (loc.X < Width && loc.X >= 0 && loc.Y >= 0 && loc.Y < Height) {
        return TerrainData[loc.X][loc.Y];
    }
    return Empty;
}
