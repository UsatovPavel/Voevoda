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
	TArray<Location> CitiesInitPos;
	void random_generate();
	void generate_enemies();
	//void generate_castles();
	//void generate_cities();

};
