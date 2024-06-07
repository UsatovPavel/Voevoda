#include "SupplyArmyInteractor.h"
#include "HAL/PlatformProcess.h"



void SupplyArmyInteractor::HandleIfTrue(AStrategist* strategist, AStructure* structure) {

    TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);

    if (!LastSupplyTimeMap.Contains(Pair)) {
        UE_LOG(LogTemp, Warning, TEXT("pair = nullptr"));
        return;
    }

    LastSupplyTimeMap[Pair]++;

    if (LastSupplyTimeMap[Pair] >= 100) {

        City* city = Cast<City>(structure);

        if (!city) {
            UE_LOG(LogTemp, Warning, TEXT("city= nullptr"));
            return;
        }

        city->replenish_army( strategist,100);

        LastSupplyTimeMap[Pair] = -1;
        RenewCityResoursesMap[structure->id] = 1;
    }

}

void SupplyArmyInteractor::HandleIfTrueForPlayer(AStructure* structure) {

    TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacter->id, structure->id);

    if (!LastSupplyTimeMap.Contains(Pair)) {
        UE_LOG(LogTemp, Warning, TEXT("pair = nullptr"));
        return;
    }

    LastSupplyTimeMap[Pair]++;

    City* city = Cast<City>(structure);

    if (!city) {
        UE_LOG(LogTemp, Warning, TEXT("city= nullptr"));
        return;
    }

    if (LastSupplyTimeMap[Pair] == 0) {
        PlayerCharacter->SupplyArmyWidget->PlayerStepOnStructure(structure->id,
            structure->manpower_growth, city->unitType);
    }

    if (LastSupplyTimeMap[Pair] >= 100) {

        int32 replenishArmySize = PlayerCharacter->SupplyArmyWidget->GetManpowerGrowthWantToSpend();

        if (replenishArmySize == 0) {
            return;
        }

        city->replenish_army(PlayerCharacter, PlayerCharacter->manpower_available);

        PlayerCharacter->SupplyArmyWidget->AfterCityreplenish(structure->manpower_growth);
        LastSupplyTimeMap[Pair] = -1;
        RenewCityResoursesMap[structure->id] = 1;
    }

}


void SupplyArmyInteractor::SetMapAndPlayerCharacter(AMyPlayerCharacter* PlayerCharacter_, TArray<AStrategist*>& strategists, TArray<AStructure*>& structures) {

    PlayerCharacter = PlayerCharacter_;
    int32  PlayerCharacterId = PlayerCharacter->id;


    FString message = FString::Printf(TEXT("Strategists size: %d, Structures size: %d"), strategists.Num(), structures.Num());
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);

    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
            LastSupplyTimeMap.Add(Pair, -1);
        }
        RenewCityResoursesMap.Add(structure->id, -1);
        TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacterId, structure->id);
        LastSupplyTimeMap.Add(Pair, -1);

    }
    seted = true;
}

bool StartegstOnStructure(Location strategistLocation, Location StructureLocation) {
    return ((strategistLocation.X == StructureLocation.X || strategistLocation.X + 1 == StructureLocation.X) &&
        (strategistLocation.Y == StructureLocation.Y || strategistLocation.Y + 1 == StructureLocation.Y));
}


void SupplyArmyInteractor::StartSupplyArmyEvent(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures)
{
    if (LastSupplyTimeMap.Num() == 0  || !PlayerCharacter) {
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("null"));
        return;
    }

    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            if (strategist->general.position == structure->position) {
                HandleIfTrue(strategist, structure);
            }
            else {
                TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
                if (!LastSupplyTimeMap.Contains(Pair)) {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pair problem"));
                    return;
                }
                LastSupplyTimeMap[Pair] = -1;
            }
        }

        if (RenewCityResoursesMap[structure->id] != -1) {
            RenewCityResoursesMap[structure->id]++;

        }
        if (RenewCityResoursesMap[structure->id] >= 500) {

            City* city = Cast<City>(structure);
            if (city) {
                city->renewCityResourses();
                RenewCityResoursesMap[structure->id] = -1;
            }
        }


        if (StartegstOnStructure(PlayerCharacter->general.position, structure->position)) {
            HandleIfTrueForPlayer(structure);
        }

        else {
            TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacter->id, structure->id);
            if (LastSupplyTimeMap[Pair] != -1) {
                PlayerCharacter->SupplyArmyWidget->PlayerMovedFromStructure();
            }
            LastSupplyTimeMap[Pair] = -1;
        }

    }
}
