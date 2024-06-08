// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleResponseModel.h"
BattleResponseModel::BattleResponseModel(TArray<AStrategist*>& strategists, Location position, const GameMap* map_ptr, AMyPlayerCharacter* player,
	AGameWorld* GameWorld) {
#ifndef BATTLES_OFF
	TArray<int32> enemy_ids = battle_funcs.get_nearby_enemies(strategists, position);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,
		FString::Printf(TEXT("amount of enemy %d"), enemy_ids.Num()));
	Army enemy_army_size(0, 0, 0);
	for (auto x : enemy_ids) {
		enemy_army_size += strategists[x]->general.army_size;
	}
	Army player_army_size = player->general.army_size;
	ArmyModifier terrain_modifyer = battle_funcs.summary_terrain_modifiers(position, map_ptr);
	ArmyModifier proportions_player_modifier = battle_funcs.calculate_proportions_modifier(player_army_size, enemy_army_size);
	ArmyModifier proportions_enemy_modifier = battle_funcs.calculate_proportions_modifier(enemy_army_size, player_army_size);
	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,
		FString::Printf(TEXT("battle player %lld"), player_army_size.Infantry + player_army_size.Cavalry + player_army_size.Archers));
		*/
	bool result = battle_funcs.calculate_battle_result(player_army_size, enemy_army_size, proportions_player_modifier * terrain_modifyer, terrain_modifyer * proportions_enemy_modifier);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("is_user_win %lld"), result));
	if (result) {
		player->general.army_size = player_army_size;
		for (auto id : enemy_ids) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				FString::Printf(TEXT("destroy BP AI_ %lld"), id));
			strategists[id]->general.is_dead = true;
			strategists[id]->Destroy();
		}
		delete_dead_strategists(strategists);
		if (strategists.Num() == 0) {
			GameWorld->is_victory = true;
		}
	}
	else {
		GameWorld->is_losed = true;
		//проигрыш
	}
	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("GameWorld->is_losed %lld"), GameWorld->is_losed));*/
#endif
}
void BattleResponseModel::delete_dead_strategists(TArray<AStrategist*>& strategists) {
	TArray<AStrategist*> alive_strategists;
	for (auto& strateg : strategists) {
		if (!strateg->general.is_dead) {
			alive_strategists.Add(strateg);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				FString::Printf(TEXT("delete from TArray AI_ %lld"), strateg->id));
		}
	}
	strategists = alive_strategists;
}
