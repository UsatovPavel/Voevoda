// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYPROJECT1040_API Army
{
public:
	Army(int32 Arch, int32 Inf, int32 Cav):Archers(Arch), Infantry(Inf), Cavalry(Cav){}
	int32 Archers;
	int32 Infantry;
	int32 Cavalry;
};
