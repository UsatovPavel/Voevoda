// Fill out your copyright notice in the Description page of Project Settings.


#include "City.h"

City::City() {}

City::~City(){}


void City::replenish_army(BaseStrategist* player_id, int32 amount) {


    int32 replenishAmount = FMath::Min(amount, player_id->manpower_available);
    replenishAmount = FMath::Min(manpower_growth, replenishAmount);


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

    manpower_growth -= replenishAmount;

}



void  City::replenish_army(AStrategist* player_id, int32 amount) {

    int32 replenishAmount = FMath::Min(amount, player_id->manpower_available);
    replenishAmount = FMath::Min(manpower_growth, replenishAmount);


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

    manpower_growth -= replenishAmount;
}

void City::renewCityResourses() {

    manpower_growth = capasity;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("renewCityResourses"));
    FString message2 = FString::Printf(TEXT("manpower_growth: %d, capasity: %d"), manpower_growth, capasity);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message2);
}

void  City::SetPosition( Location pos, int32 id_) {
    int32 unitTypeNumber = FMath::RandRange(0, 2);
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
    position = pos;
    id = id_;
}



