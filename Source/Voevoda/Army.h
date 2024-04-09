// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class VOEVODA_API Army
{
public:
	Army():Archers(FMath::RandRange(0, 10)), Infantry(FMath::RandRange(0, 10)), Cavalry(FMath::RandRange(0, 10)){}
	Army(int32 Arch, int32 Inf, int32 Cav):Archers(Arch), Infantry(Inf), Cavalry(Cav){}
	int32 Archers;
	int32 Infantry;
	int32 Cavalry;
};
