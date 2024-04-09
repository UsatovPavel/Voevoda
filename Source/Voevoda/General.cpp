// Fill out your copyright notice in the Description page of Project Settings.


#include "General.h"
void General::move(Location new_location) {
	position = new_location;
}
General::General() :army_size({ 0, 0, 0 }), position({ 0, 0 }), is_dead(true) {}

General::General(Location init_loc) : army_size({ 0, 0, 0 }), position(init_loc), is_dead(true) {}