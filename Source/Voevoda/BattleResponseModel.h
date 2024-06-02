// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerCharacter.h"
#include "Strategist.h"
#include "GameMap.h"
#include "TerrainType.h"
#include "GameWorld.h"
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
inline ArmyModifier calculate_terrain_modifier(TerrainType x, int32 coef) {
	ArmyModifier modifier(0, 0, 0);//êàâà øòðàôóåòñÿ, ïåõîòà è ëó÷íèêè áàôàþòñÿ
	switch (x) {
	case Woods:
		modifier.Infantry += 1;
		modifier.Archers -= 1;
		modifier.Cavalry -= 1;
		break;
	case Mountains:
		modifier.Archers += 2;
		break;
	case Water:
		modifier.Cavalry -= 1;
		break;
	case Castle:
		modifier.Infantry += 2;
		modifier.Archers += 1;
		modifier.Cavalry -= 5;
		break;
	default:
		break;
	}
	return modifier * coef;
}
inline ArmyModifier summary_terrain_modifiers(Location position, const GameMap& map) {
	ArmyModifier terrain_modifyer(100, 100, 100);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			TerrainType t_type = map.get_terrain({ position.X + i, position.Y + j });
			int32 coef = 1;//åñëè óãëîâûå
			if (i == 0 || j == 0) { coef = 5; }//åñëè ñîñåäíèå
			terrain_modifyer += calculate_terrain_modifier(t_type, coef);
		}
	}
	return terrain_modifyer;
}
inline ArmyModifier calculate_proportions_modifier(Army army, Army enemy_army) {
	ArmyComposition player_composition(army);
	ArmyComposition enemy_composition(enemy_army);
	ArmyModifier modifyer(100, 100, 100);
	if (player_composition.Arch >= 0.7 && enemy_composition.Cav >= 0.3) {//êàâàëåðèÿ èñòðåáëÿåò ëó÷íèêîâ
		modifyer.Archers -= static_cast<float>(1 - player_composition.Arch) / 0.3 * 100;
	}
	if (player_composition.Cav >= 0.7 && enemy_composition.Inf >= 0.3)//ïåõîòà øòðàôóåòñÿ êàâàëåðèþ
		modifyer.Cavalry -= static_cast<float>(1 - player_composition.Cav) / 0.3 * 50 * (enemy_composition.Inf) / 0.3;
	if (player_composition.Inf >= 0.7 && enemy_composition.Arch >= 0.3)//ëó÷íèêè ðàññòðåëèâàþò ïåõîòó
		modifyer.Infantry -= static_cast<float>(1 - player_composition.Inf) / 0.3 * 100;
	return modifyer;
}
inline bool calculate_battle_result(Army& player_army, Army enemy_army, ArmyModifier player_modifier, ArmyModifier enemy_modifier) {
	float user_strength = player_army.calculate_strength(player_modifier);
	float enemy_strength = enemy_army.calculate_strength(enemy_modifier);
	if (user_strength < enemy_strength) {
		return false;//ïðîèãðûø òóò äîëæåí âûêèäûâàòüñÿ
	}
	player_army.Archers = player_army.Archers * ((user_strength - enemy_strength) / user_strength);
	player_army.Infantry = player_army.Infantry * ((user_strength - enemy_strength) / user_strength);
	player_army.Cavalry = player_army.Cavalry * ((user_strength - enemy_strength) / user_strength);
	return true;
}
inline TArray<int32> get_nearby_enemies(TArray<AStrategist*>& strategists, Location position) {
	TArray<int32> enemy_ids;
	for (int id = 1; id < strategists.Num(); id++) {
		int32 dist = abs(strategists[id]->general.position.X - position.X) +
			abs(strategists[id]->general.position.Y - position.Y);
		if (dist <= 3) {
			enemy_ids.Push(id);
		}
	}
	return enemy_ids;
}
class VOEVODA_API BattleResponseModel
{
public:
	void delete_dead_strategists(TArray<AStrategist*>& strategists) {
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
	BattleResponseModel(TArray<AStrategist*>& strategists, Location position, const GameMap& map, AMyPlayerCharacter* player,
		AGameWorld* GameWorld) {
#ifndef BATTLES_OFF
		TArray<int32> enemy_ids = get_nearby_enemies(strategists, position);
		Army enemy_army_size(0, 0, 0);
		for (auto x : enemy_ids) {
			enemy_army_size += strategists[x]->general.army_size;
		}
		Army player_army_size = player->general.army_size;
		ArmyModifier terrain_modifyer = summary_terrain_modifiers(position, map);
		ArmyModifier proportions_player_modifier = calculate_proportions_modifier(player_army_size, enemy_army_size);
		ArmyModifier proportions_enemy_modifier = calculate_proportions_modifier(enemy_army_size, player_army_size);
		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White,
			FString::Printf(TEXT("battle player %lld"), player_army_size.Infantry + player_army_size.Cavalry + player_army_size.Archers));
			*/
		bool result = calculate_battle_result(player_army_size, enemy_army_size, proportions_player_modifier * terrain_modifyer, terrain_modifyer * proportions_enemy_modifier);
		if (result) {
			player->general.army_size = player_army_size;
			for (auto id : enemy_ids) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
					FString::Printf(TEXT("destroy BP AI_ %lld"), id));
				strategists[id]->general.is_dead = true;
				strategists[id]->Destroy();
			}
			delete_dead_strategists(strategists);
		}
		else {
			GameWorld->is_losed = true;
			//ïðîèãðûø
		}
		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("GameWorld->is_losed %lld"), GameWorld->is_losed));*/
#endif
	}
};
