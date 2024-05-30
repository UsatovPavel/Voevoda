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