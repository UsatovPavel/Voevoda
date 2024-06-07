#pragma once

#include "CoreMinimal.h"
#include "BaseStrategist.h"
//#include "MyPlayerCharacter.h"
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

    ~City();

    void  replenish_army(BaseStrategist* player_id, int32 amount);
    void  replenish_army(AStrategist* player_id, int32 amount);
    void renewCityResourses();

    void SetPosition( Location pos, int32 id_);

    UnitType unitType;
};
