// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector2D.h"
/**
 * 
 */
class VOEVODA_API Scout
{
public:
	int32 missions_spy;
	bool active;
	int32 passed_time;
	int32 mission_time;
	FVector2D target_position;
	void execute_scout(FVector2D input);//��������� ����������

};
