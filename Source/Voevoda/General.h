// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Army.h"
#include "Location.h"
#include "Math/Vector.h"
/**
 *
 */
class VOEVODA_API General
{
public:
	General();
	General(Location init_loc);
	Army army_size;
	Location position;
	bool is_dead = false;
	double speed;
	int kills;
	void move(Location new_location);
	void update_pos(FVector UE_coordinates);//verified
};
