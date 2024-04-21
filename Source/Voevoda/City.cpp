// Fill out your copyright notice in the Description page of Project Settings.


#include "City.h"

City::City()
{
    /*for (TActorIterator<GameMap> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {

        GameMap_ptr =ActorItr;
    }*/
}

City::~City()
{
}

void City::replenish_army(AStrategist* player_id) {

    if (owner->id == player_id->id || player_id->is_dead()) {
        return;
    }

    int32 replenishAmount = FMath::Min(manpower_growth, player_id->manpower_available)/5;

    switch (unitType) {
        case Archers:
            player_id->general.army_size.Archers += replenishAmount;
            break;
        case Infantry:
            player_id->general.army_size.Infantry += replenishAmount;
            break;
        case Cavalry:
            player_id->general.army_size.Cavalry += replenishAmount;
            break;
     }
     
     owner->manpower_available -= replenishAmount;

}
//for (auto& controlledCity : player_id->structures_controlled) {
//    if (controlledCity == id) {
//        return;
//    }
//}
