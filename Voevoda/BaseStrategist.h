// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/UnrealString.h"
#include "Containers/Array.h"
#include "TerrainType.h"
#include "General.h"
#include "Scout.h"
#include "PlayerGameSessionStatistic.h"
/**
 *
 */
class VOEVODA_API BaseStrategist
{
	bool dead;
public:
	const int32 defaultScoutsNumder = 5;
	int32 id;
	FString username;
	TArray<int32> structures_controlled;
	int32 manpower_available = 50;
	TArray<TArray<TerrainType>> visited_tiles;
	General general;
	TArray<Scout> scouts;
	PlayerGameSessionStatistic session_stats;
	bool is_dead() {
		return dead;
	}
	Location get_location() {
		return general.position;
	}
	BaseStrategist() {};
	BaseStrategist(Location init_loc);
};
