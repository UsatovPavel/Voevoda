// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Structure.h"
#include "GameMap.h"

UENUM()
enum UnitType {
    Archers UMETA(DisplayName = "Archers"),
    Infantry UMETA(DisplayName = "Infantry"),
    Cavalry UMETA(DisplayName = "Cavalry"),
};

class VOEVODA_API City : public AStructure
{
public:
	City();

	City(Location init_pos, AStrategist* owner_) : AStructure(init_pos), owner(owner_)
	{
        int32 unitTypeNumber = FMath::RandRange(0,2);
        switch (unitTypeNumber) {
        case 0:
            unitType = Archers;
            break;
        case 1:
            unitType = Infantry;
            break;
        case 2:
            unitType = Cavalry;
            break;
        }

	}

	~City();

	void replenish_army(AStrategist* player_id);
    void renewCityResourses();

    void SetOwnerPosition (AStrategist* player_id, Location pos, int32 id_);
    AStrategist* GetOwner();

private:
    //void PostInitializeComponents();
	UnitType unitType;
    AStrategist* owner;
};
