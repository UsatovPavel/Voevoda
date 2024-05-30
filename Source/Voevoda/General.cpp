// Fill out your copyright notice in the Description page of Project Settings.


#include "General.h"
void General::move(Location new_location) {
	position = new_location;
}
void General::update_pos(FVector UE_coordinates) {//verified
	float move_X = UE_coordinates.X;
	float move_Y = UE_coordinates.Y;
	position = { abs(static_cast<int32>(move_X) / 64), abs(static_cast<int32>(move_Y) / 64) };
}
General::General() :army_size({ 0, 0, 0 }), position({ 0, 0 }), is_dead(false) {}

General::General(Location init_loc) : army_size({ 0, 0, 0 }), position(init_loc), is_dead(false) {}