#pragma once

#include "Strategist.h"
#include "Structure.h"
#include "City.h"
#include "MyPlayerCharacter.h"
#include "UStructureInfoWidget.h"

class AMyPlayerCharacter;

class VOEVODA_API SupplyArmyInteractor
{
private:

    AMyPlayerCharacter* PlayerCharacter = nullptr;
    TMap<TPair<int32, int32>, int32> LastSupplyTimeMap;
    TMap<int32, int32> RenewCityResoursesMap;
    bool seted = false;
    void HandleIfTrue(AStrategist* strategist, AStructure* structure);
    void HandleIfTrueForPlayer(AStructure* structure);

public:
    void StartSupplyArmyEvent(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures);

    bool is_seted() {
        return(seted);
    }

    void SetMapAndPlayerCharacter(AMyPlayerCharacter* PlayerCharacter_, TArray<AStrategist*>& strategists, TArray<AStructure*>& structures);

    SupplyArmyInteractor() = default;
    ~SupplyArmyInteractor() = default;

};