// Fill out your copyright notice in the Description page of Project Settings.


#include "Scout.h"
#include "MapPainter.h"

Scout::Scout() {}

Scout::Scout(bool is_player_) {
	is_player = is_player_;
}

void Scout::TickFromStrategist(AMapPainter* painter_ptr)
{

	if (active && mission_time > passed_time) {
		passed_time++;
	}
	else if (active) {
		active = 0;
		passed_time = 0;
		painter_ptr->UpdateRhombVision(target_position.X, target_position.Y, 5, VisionType::Unseen);
	}

	if (is_player && active) {
		painter_ptr->UpdateRhombVision(target_position.X, target_position.Y, 5, VisionType::Seen);
	}


}


void Scout::execute_scout(Location input) {
	if (!active) {
		target_position = input;
		active = 1;
	}
}