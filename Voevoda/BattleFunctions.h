// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerCharacter.h"
#include "Strategist.h"
#include "GameMap.h"
#include "TerrainType.h"
#include "GameWorld.h"

/**
 *
 */
class VOEVODA_API BattleFunctions
{
public:
	ArmyModifier calculate_terrain_modifier(TerrainType x, int32 coef);
	ArmyModifier summary_terrain_modifiers(Location position, const GameMap* map);
	ArmyModifier calculate_proportions_modifier(Army army, Army enemy_army);
	bool calculate_battle_result(Army& player_army, Army enemy_army, ArmyModifier player_modifier, ArmyModifier enemy_modifier);
	bool bool_battle_result(Army& player_army, Army enemy_army, ArmyModifier player_modifier, ArmyModifier enemy_modifier);
	TArray<int32> get_nearby_enemies(TArray<AStrategist*>& strategists, Location position);
	bool is_player_win(AStrategist* strateg_ptr, Location position, const GameMap* map, AMyPlayerCharacter* player_ptr,
		AGameWorld* GameWorld);
};
