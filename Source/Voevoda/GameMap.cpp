// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"

GameMap::GameMap() {
	Height = FMath::RandRange(100, 500);
	Width = FMath::RandRange(100, 500);
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
	float x = Width * Height / 100;//one Army_position for 33^2 tiles
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
void GameMap::generate_cities() {
	for (Location enemy : GeneralsInitPos) {
		while (true) {
			int32 X = FMath::RandRange(enemy.x-5, enemy.x + 5);
			int32 Y = FMath::RandRange(enemy.y-5, enemy.y + 5);
			if (TerrainData[X][Y] == Grass) {
				TerrainData[X][Y] = Castle;
				CitiesInitPos.Add({ X, Y });//Add<=>push_back
				break;
			}
		}
	}
}