// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_MoveModel.h"
TOptional<AStructure*> AI_MoveModel::get_nearest_structure(AStrategist* strateg_ptr, const TArray<AStructure*>& structures) {
	int min_dist = 10000;
	TOptional<AStructure*> nearest_structure;
	for (auto structure : structures) {
		if (structure->position.Manh_dist(strateg_ptr->general.position) <= min_dist) {
			nearest_structure.Emplace(structure);
			min_dist = structure->position.Manh_dist(strateg_ptr->general.position);
		}
	}
	return nearest_structure;
}
void AI_MoveModel::set_strateg_position(AStrategist* strateg_ptr, Location loc) {
	strateg_ptr->general.position = loc;
	strateg_ptr->SetActorLocation(strateg_ptr->get_location().UE_coordinates());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("step to %d %d"), loc.X, loc.Y));
}
bool AI_MoveModel::step_to_location(AStrategist* strateg_ptr, Location position, const GameMap* map_ptr, bool attack) {//атакует - туда, нет - оттуда
	MoveOrder dfs(strateg_ptr->general.position, map_ptr, 15);
	TOptional<TArray<Location>> order = dfs.get_locations_order(position);
	if (order.IsSet()) {
		if (attack) {
			set_strateg_position(strateg_ptr, order.GetValue()[0]);
			return true;
		}
		Location tile_now = strateg_ptr->general.position;
		FIntPoint delta = (tile_now - order.GetValue()[0]);
		if (map_ptr->is_tile_valid({ tile_now.X + delta.X, tile_now.Y + delta.Y })) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("180 run")));
			set_strateg_position(strateg_ptr, { tile_now.X + delta.X, tile_now.Y + delta.Y });
		}
		else {
			TArray<Location> walkable_adj = map_ptr->get_walkable_adj(tile_now);
			for (int i = 0; i < walkable_adj.Num(); i++) {
				if (walkable_adj[i] != order.GetValue()[0]) {
					set_strateg_position(strateg_ptr, { walkable_adj[i] });
				}
			}
		}
		return true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("DFS failed")));
	return false;
}
void AI_MoveModel::random_step(AStrategist* strateg_ptr, const GameMap* map_ptr) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("random step begin")));
	TArray<Location> walkable_adj = map_ptr->get_walkable_adj(strateg_ptr->general.position);
	int32 rand = FMath::RandRange(0, walkable_adj.Num() - 1);
	set_strateg_position(strateg_ptr, walkable_adj[rand]);
}
TArray<AStructure*> AI_MoveModel::get_wanted_structures(AStrategist* strateg_ptr, const TArray<AStructure*>& structures) {
	TArray<AStructure*> wanted_structures;
	for (auto structure : structures) {
		if (structure->position.Manh_dist(strateg_ptr->general.position) <= 7) {
			wanted_structures.Add(structure);
		}
	}
	return wanted_structures;
}