// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameWorld.h"
#include "BattleResponseModel.h"
#include "BattleFunctions.h"
#include "MoveOrder.h"
/**
 *
 */
class VOEVODA_API AI_MoveModel
{
public:
	BattleFunctions battle_funcs;
	TArray<AStructure*> get_wanted_structures(AStrategist* strateg_ptr, const TArray<AStructure*>& structures);
	TOptional<AStructure*> get_nearest_structure(AStrategist* strateg_ptr, const TArray<AStructure*>& structures);
	void set_strateg_position(AStrategist* strateg_ptr, Location loc);
	bool step_to_location(AStrategist* strateg_ptr, Location position, const GameMap* map_ptr, bool attack = true);
	void random_step(AStrategist* strateg_ptr, const GameMap* map_ptr);
	AI_MoveModel(AStrategist* strateg_ptr, const TArray<AStructure*>& structures, AMyPlayerCharacter* player_ptr, GameMap* map_ptr, AGameWorld* game_world) {
		if (strateg_ptr->User_near) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("see player"))); }
		if (strateg_ptr->User_near) {
			bool attack = !(battle_funcs.is_player_win(strateg_ptr, player_ptr->general.position, map_ptr, player_ptr, game_world));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("attack %d"), attack));
			if (step_to_location(strateg_ptr, player_ptr->get_location(), map_ptr, attack)) {
				return;
			}
		}
		TArray<AStructure*> wanted_structures = get_wanted_structures(strateg_ptr, structures);
		TOptional<AStructure*> nearest_structure = get_nearest_structure(strateg_ptr, wanted_structures);
		if (nearest_structure.IsSet()) {
			if (step_to_location(strateg_ptr, nearest_structure.GetValue()->position, map_ptr)) {
				return;
			}
		}
		random_step(strateg_ptr, map_ptr);
	}
};
