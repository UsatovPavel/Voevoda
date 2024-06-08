// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector2D.h"
#include "Location.h"

class AMapPainter;
/**
 * 
 */
class VOEVODA_API Scout
{
public:

	int32 missions_spy;
	bool active = 0;
	bool is_player = 0;
	int32 passed_time = 0;
	int32 mission_time = 1000;
	Location  target_position;

	Scout(bool is_player_);
	Scout();

	void execute_scout(Location input);
	void TickFromStrategist(AMapPainter* painter_ptr_);

};
