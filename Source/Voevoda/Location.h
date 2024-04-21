// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class VOEVODA_API Location
{
public:
	int32 x;
	int32 y;
	Location(): x(0), y(0){ }
	Location(const int32 x_, const int32 y_):x(x_), y(y_) {}

	friend bool operator==(const Location& lhs, const Location& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	friend bool operator!=(const Location& lhs, const Location& rhs)
	{
		return !(lhs==rhs);
	}

};
