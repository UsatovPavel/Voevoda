#include "GameWorld.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

AGameWorld::AGameWorld() {

    PrimaryActorTick.bCanEverTick = true;

}

void AGameWorld::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
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
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("painter_ptr is nullptr."));
    }
}