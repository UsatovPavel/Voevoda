// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerCharacter.h"
#include "Strategist.h"
#include "GameMap.h"
#include "TerrainType.h"
#include "GameWorld.h"
#include "BattleFunctions.h"
//#define BATTLES_OFF
/**
	 Grass UMETA(DisplayName = "Grass"),
	Woods UMETA(DisplayName = "Woods"),
	Mountains UMETA(DisplayName = "Mountains"),
	Water UMETA(DisplayName = "Water"),
	Army_position UMETA(DisplayName = "Army position"),
	Castle UMETA(DisplayName = "Castle"),
	Empty UMETA(DisplayName = "Empty"),
 */
class VOEVODA_API BattleResponseModel
{
public:
	BattleFunctions battle_funcs;
	void delete_dead_strategists(TArray<AStrategist*>& strategists);
	BattleResponseModel(TArray<AStrategist*>& strategists, Location position, const GameMap* map_ptr, AMyPlayerCharacter* player,
		AGameWorld* GameWorld);
};
