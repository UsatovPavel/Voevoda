// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Army.h"
#include "Location.h"
/**
 * 
 */
class MYPROJECT1040_API General
{
public:
	General();
	Army army_size;
	Location position;
	bool is_dead;
	double speed;
	int kills;
	void move(Location new_location);
};
