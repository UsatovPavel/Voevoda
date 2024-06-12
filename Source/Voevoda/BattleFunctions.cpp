// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleFunctions.h"
ArmyModifier BattleFunctions::calculate_terrain_modifier(TerrainType x, int32 coef) {
	ArmyModifier modifier(0, 0, 0); //кава штрафуется, пехота и лучники бафаются
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
ArmyModifier BattleFunctions::summary_terrain_modifiers(Location position, const GameMap* map) {
	ArmyModifier terrain_modifyer(100, 100, 100);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			TerrainType t_type = map->get_terrain({ position.X + i, position.Y + j });
			int32 coef = 1;//если угловые
			if (i == 0 || j == 0) { coef = 5; }//если соседние
			terrain_modifyer += calculate_terrain_modifier(t_type, coef);
		}
	}
	return terrain_modifyer;
}
ArmyModifier BattleFunctions::calculate_proportions_modifier(Army army, Army enemy_army) {
	ArmyComposition player_composition(army);
	ArmyComposition enemy_composition(enemy_army);
	ArmyModifier modifyer(100, 100, 100);
	if (player_composition.Arch >= 0.7 && enemy_composition.Cav >= 0.3) {//кавалерия истребляет лучников
		modifyer.Archers -= static_cast<float>(1 - player_composition.Arch) / 0.3 * 100;
	}
	if (player_composition.Cav >= 0.7 && enemy_composition.Inf >= 0.3)//пехота штрафуется кавалерию
		modifyer.Cavalry -= static_cast<float>(1 - player_composition.Cav) / 0.3 * 50 * (enemy_composition.Inf) / 0.3;
	if (player_composition.Inf >= 0.7 && enemy_composition.Arch >= 0.3)//лучники расстреливают пехоту
		modifyer.Infantry -= static_cast<float>(1 - player_composition.Inf) / 0.3 * 100;
	return modifyer;
}
bool BattleFunctions::calculate_battle_result(Army& player_army, Army enemy_army, ArmyModifier player_modifier, ArmyModifier enemy_modifier) {
	float user_strength = player_army.calculate_strength(player_modifier);
	float enemy_strength = enemy_army.calculate_strength(enemy_modifier);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("strength user %f enemy %f"), user_strength, enemy_strength));
	if (user_strength < enemy_strength) {
		return false;//проигрыш тут должен выкидываться
	}
	player_army.Archers = player_army.Archers * ((user_strength - enemy_strength) / user_strength);
	player_army.Infantry = player_army.Infantry * ((user_strength - enemy_strength) / user_strength);
	player_army.Cavalry = player_army.Cavalry * ((user_strength - enemy_strength) / user_strength);
	return true;
}
bool BattleFunctions::bool_battle_result(Army& player_army, Army enemy_army, ArmyModifier player_modifier, ArmyModifier enemy_modifier) {
	float user_strength = player_army.calculate_strength(player_modifier);
	float enemy_strength = enemy_army.calculate_strength(enemy_modifier);
	return user_strength >= enemy_strength;
}
TArray<int32> BattleFunctions::get_nearby_enemies(TArray<AStrategist*>& strategists, Location position) {
	TArray<int32> enemy_ids;
	for (int id = 0; id < strategists.Num(); id++) {
		int32 dist = abs(strategists[id]->general.position.X - position.X) +
			abs(strategists[id]->general.position.Y - position.Y);
		if (dist <= 3) {
			enemy_ids.Push(id);
		}
	}
	return enemy_ids;
}
bool BattleFunctions::is_player_win(AStrategist* strateg_ptr, Location position, const GameMap* map, AMyPlayerCharacter* player_ptr,
	AGameWorld* GameWorld) {
	Army enemy_army_size = strateg_ptr->general.army_size;
	Army player_army_size = player_ptr->general.army_size;
	ArmyModifier terrain_modifyer = summary_terrain_modifiers(position, map);
	ArmyModifier proportions_player_modifier = calculate_proportions_modifier(player_army_size, enemy_army_size);
	ArmyModifier proportions_enemy_modifier = calculate_proportions_modifier(enemy_army_size, player_army_size);
	bool result = bool_battle_result(player_army_size, enemy_army_size, proportions_player_modifier * terrain_modifyer, terrain_modifyer * proportions_enemy_modifier);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("result %d"), result));
	return result;
}