// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Location.h"
#include "GameMap.h"
#include "Algo/Reverse.h"
/**
 *
 */
class VOEVODA_API MoveOrder {
public:
	Location init_location;
	TArray<Location> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	TArray<TArray<bool>> visited_tiles;
	TArray<TArray<Location>> ancestors;
	void init_arrays(const GameMap* map_ptr) {
		TArray<bool> DefaultStrip;
		DefaultStrip.Init(false, map_ptr->Height);
		visited_tiles.Init(DefaultStrip, map_ptr->Width);
		TArray<Location> DefaultLocStrip;
		DefaultLocStrip.Init({ 0, 0 }, map_ptr->Height);
		ancestors.Init(DefaultLocStrip, map_ptr->Width);
	}
	MoveOrder(Location init, const GameMap* map_ptr, int32 steps_amount) {
		init_location = init;
		init_arrays(map_ptr);
		visited_tiles[init.X][init.Y] = true;
		TArray<Location> step_tiles = { init };
		for (int i = 0; i < steps_amount; i++) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("on step %d "), i));
			TArray<Location> new_step_tiles;
			for (auto tile : step_tiles) {
				for (auto dir : directions) {
					FIntPoint new_tile = tile + dir;
					if (map_ptr->is_tile_valid({ new_tile.X, new_tile.Y }) && visited_tiles[new_tile.X][new_tile.Y] == false) {
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
						//	FString::Printf(TEXT("set true %d %d"), new_tile.X, new_tile.Y ));
						visited_tiles[new_tile.X][new_tile.Y] = true;
						ancestors[new_tile.X][new_tile.Y] = tile;
						new_step_tiles.Add({ new_tile.X, new_tile.Y });
					}
				}
			}
			step_tiles = new_step_tiles;
		}
	}
	TOptional<TArray<Location>> get_locations_order(Location destination) {
		TArray<Location> order;
		if (visited_tiles[destination.X][destination.Y]) {
			while (destination != init_location) {
				order.Add(destination);
				destination = ancestors[destination.X][destination.Y];
			}
		}
		Algo::Reverse(order);
		if (order.Num() == 0) {
			return TOptional<TArray<Location>>();
		}
		else {
			return TOptional<TArray<Location>>(order);
		}
	}
};
