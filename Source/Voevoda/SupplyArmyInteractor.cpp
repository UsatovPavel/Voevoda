#include "SupplyArmyInteractor.h"
#include "HAL/PlatformProcess.h"



void SupplyArmyInteractor::HandleIfTrue2(AStrategist* strategist, AStructure* structure) {


    TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
    if (!LastSupplyTimeMap.Contains(Pair)) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pair problem HandleIfTrue2"));
        return;
    }

    LastSupplyTimeMap[Pair]++;

    //FString message = FString::Printf(TEXT("LastSupplyTimeMap2[Pair]: %d "), LastSupplyTimeMap2[Pair]);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
   // FString message2 = FString::Printf(TEXT("1: %d, 2: %d "), strategist->id, structure->id);
   // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message2);

   if (LastSupplyTimeMap[Pair] >= 100) {
       // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("citySupplyArmyInteractor2222222"));
        City* city = Cast<City>(structure);
        if (!city) {
            return;
        }

        city->replenish_army(strategist);
        LastSupplyTimeMap[Pair] = -1.;
        RenewCityResoursesMap[structure->id] = 1;
        Pair = TPair<int32, int32>(strategist->id, structure->id);
        FString message6 = FString::Printf(TEXT("strategist: %d, structure: %d"), strategist->id, structure->id);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message6);
        if (LastSupplyTimeMap.Contains(Pair))
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("still contains"));
        }
        else {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("not contains"));
        }
    }

}


void SupplyArmyInteractor::SetMapAndPlayerCharacter(AMyPlayerCharacter* PlayerCharacter_, TArray<AStrategist*>& strategists, TArray<AStructure*>& structures) {

    PlayerCharacter = PlayerCharacter_;
    int32  PlayerCharacterId = PlayerCharacter->Strategist->id;

    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
            LastSupplyTimeMap.Add(Pair, -1);
        }
        RenewCityResoursesMap.Add(structure->id, -1);
        TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacterId, structure->id);
        LastSupplyTimeMap.Add(Pair, -1);

    }

    FString message4 = FString::Printf(TEXT("LastSupplyTimeMap : %d"), LastSupplyTimeMap.Num());
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message4);

    seted = true;
}

bool StartegstOnStructure(Location strategistLocation, Location StructureLocation) {
    return ((strategistLocation.x == StructureLocation.x || strategistLocation.x + 1 == StructureLocation.x) &&
        (strategistLocation.y == StructureLocation.y || strategistLocation.y + 1  == StructureLocation.y ) );
}


void SupplyArmyInteractor::StartSupplyArmyEvent2(TArray<AStrategist*>& strategists, TArray<AStructure*>& structures)
{
    if (LastSupplyTimeMap.Num() == 0 || !PlayerCharacter) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("null"));
        return;
    }


   /* FString message = FString::Printf(TEXT("Strategists size: %d, Structures size: %d"), strategists.Num(), structures.Num());
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);*/

    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            if (strategist->general.position == structure->position) {
                HandleIfTrue2(strategist, structure);
            }
            else {
                TPair<int32, int32> Pair = TPair<int32, int32>(strategist->id, structure->id);
                if (LastSupplyTimeMap.Contains(Pair))
                {
                    LastSupplyTimeMap[Pair] = -1;
                }
                else
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pair problem"));
                    FString message = FString::Printf(TEXT("strategist: %d, structure: %d"), strategist->id, structure->id);
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
                    return;
                }
            }
        }

       /* FString message = FString::Printf(TEXT("strategist: %d, structure: %d"), (strategists.Num(), structures.Num()));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);*/
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
        if (PlayerCharacter && StartegstOnStructure(PlayerCharacter->Strategist->general.position,structure->position)) {
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("on  structure"));
            HandleIfTrue2(PlayerCharacter->Strategist, structure);
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("on  structure"));
        }
        else if (PlayerCharacter) {
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not on  structure"));
            TPair<int32, int32> Pair = TPair<int32, int32>(PlayerCharacter->Strategist->id, structure->id);
            LastSupplyTimeMap[Pair] = -1;
           // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not on  structure"));
        }
    }
}



