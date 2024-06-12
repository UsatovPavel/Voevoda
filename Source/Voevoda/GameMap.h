// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TerrainType.h"
#include "Location.h"
/**
 *
 */
class VOEVODA_API GameMap
{
public:
	GameMap();
	int32 Width = 500;
	int32 Height = 300;
	TArray<TArray<TerrainType>> TerrainData;
	TArray<Location> GeneralsInitPos;
	TArray<Location> CastlesInitPos;
	TerrainType get_terrain(Location loc) const;
	void random_generate();
	void generate_enemies();
	void generate_castles();
	void random_woods_and_mountains();
        void random_river();
		TArray<Location> get_walkable_adj(Location position) const;
		bool is_tile_valid(Location position) const;
private:
	void dfs_for_random_river(int32 XValue, int32 YValue, TArray<TArray<int32>>& VisitedArray);
	bool IsValid(int32 XValue, int32 YValue);


};
