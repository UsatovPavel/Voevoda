#include "GameWorld.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

AGameWorld::AGameWorld() {

    PrimaryActorTick.bCanEverTick = true;

}
AGameWorld::~AGameWorld() {
    delete SupplyArmyInteractor;
}
void AGameWorld::Tick(float DeltaTime) {

    Super::Tick(DeltaTime);

    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            if (strategist->general.position == structure->position) {
                FSupplyArmyInteractor::StartSupplyArmyEvent(strategist, structure);
            }
        }
    }
}

void AGameWorld::BeginPlay() {
    Super::BeginPlay();

    for (TActorIterator<AMapPainter> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {

        painter_ptr = Cast<AMapPainter>(*ActorItr);
        map_ptr = &(painter_ptr->map);
    }

    if (painter_ptr) {
        for (auto& general_pos : map_ptr->GeneralsInitPos) {
            AStrategist new_strategist(general_pos);
            strategists.Add(&new_strategist);
        }
        for (auto& castle_pos : map_ptr->CastlesInitPos) {
            AStructure new_castle(castle_pos);
            structures.Add(&new_castle);
        }
        for (int32 id = 1; id <= map_ptr->CitiesInitPos.Num(); id++) {
            City new_city(map_ptr->CitiesInitPos[id-1], strategists[id-1]);
            structures.Add(&new_city);
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("painter_ptr is nullptr."));
    }

}