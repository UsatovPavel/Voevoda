// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Strategist.h"
#include "MyPlayerCharacter.h"
/**
 *
 */
class VOEVODA_API VisibilityController
{
public:
	VisibilityController(AStrategist* strateg_ptr, AMyPlayerCharacter* player_ptr) {
		int32 distance = (strateg_ptr->general.position).Manh_dist(player_ptr->general.position);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("distanse % lld"), distance));
		if (distance <= 7) {
			strateg_ptr->User_near = true;
		}
		else {
			strateg_ptr->User_near = false;
		}
	}
};
