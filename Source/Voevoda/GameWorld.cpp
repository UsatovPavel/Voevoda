#include "GameWorld.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Templates/SharedPointer.h"
#include "BattleResponseModel.h"
#include "VisibilityController.h"
//#define BATTLES
#define SPAWN
AGameWorld::AGameWorld() {

    PrimaryActorTick.bCanEverTick = true;

}

void AGameWorld::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
#ifdef BATTLES
    VisibilityController(strategists[0], player_ptr);
    for (auto strateg_ptr : strategists) {
        //VisibilityController(strateg_ptr, player_ptr);
    }
    TOptional<Location> battle_location;
    for (int i = 0; i < strategists.Num(); i++) {
        if (((strategists[i]->general.position).Manh_dist(player_ptr->general.position) <= 1) && (player_ptr->general.position != Location(0, 0))) {
            battle_location = strategists[i]->general.position;
        }
    }
    if (battle_location.IsSet()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
            FString::Printf(TEXT("battle_location x %lld"), battle_location.GetValue().X));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
            FString::Printf(TEXT("battle_location y %lld"), battle_location.GetValue().Y));
        BattleResponseModel(strategists, battle_location.GetValue(), *map_ptr, player_ptr, this);
    }
    if (is_losed) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("is_losed %lld"), strategists.Last()->general.army_size.Infantry));
    }
#endif
}
void AGameWorld::spawn_objects() {
    if (painter_ptr && player_ptr) {
#ifdef SPAWN
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("begin spawning"));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("size %lld"), map_ptr->GeneralsInitPos.Num()));
        if (map_ptr->GeneralsInitPos.Num() == 0) { UE_LOG(LogTemp, Warning, TEXT("GameWorld get empty array")); return; }
        for (auto& general_pos : map_ptr->GeneralsInitPos) {
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("spawn general %f %f %f"), general_pos.UE_coordinates().X, general_pos.UE_coordinates().Y, general_pos.UE_coordinates().Z));
            TOptional<AStrategist*> Spawned_strateg = spawn_strategist(general_pos.UE_coordinates());
            if (Spawned_strateg) {
                strategists.Add(Cast<AStrategist>(Spawned_strateg.GetValue()));
                strategists.Last()->general.army_size.rand(strategists.Num());//this seed rand() in army;
            }
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("i seed generator this number %lld"), strategists.Last()->general.army_size.Infantry));
        }
        //strategists[0]->general.army_size.Infantry = 1000;
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("infantry deleted strategist %lld"), strategists[0]->general.army_size.Infantry));
        //strategists[0]->Destroy();

        for (auto& castle_pos : map_ptr->CastlesInitPos) {
            //AStructure new_castle(castle_pos);
            //structures.Add(&new_castle);
        }
        UE_LOG(LogTemp, Display, TEXT("GameWorld spawn objects OK"));
#endif
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("GameWorld spawn FAILED"));
    }
}
void AGameWorld::BeginPlay() {
    Super::BeginPlay();

    for (TActorIterator<AMapPainter> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {

        painter_ptr = Cast<AMapPainter>(*ActorItr);
        map_ptr = &(painter_ptr->map);
    }
    for (TActorIterator<AMyPlayerCharacter> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {
        player_ptr = Cast<AMyPlayerCharacter>(*ActorItr);
    }
    if (map_ptr && player_ptr) {
        painter_ptr->player_ptr=player_ptr;
        painter_ptr->GameWorld_ptr = this;
        UE_LOG(LogTemp, Display, TEXT("GameWorld Init complete, now generate TileMap"));
        painter_ptr->generate_TileMap();
    }
    else {
       UE_LOG(LogTemp, Warning, TEXT("painter_ptr(MAP) or player_ptr(UserCharacter) is nullptr."));
    }
}
TOptional<AStrategist*> AGameWorld::spawn_strategist(FVector UE_coordinates) {
    TSubclassOf<AStrategist> StrategToSpawn = BP_Strategist;
    AStrategist* NewObj = GetWorld()->SpawnActor<AStrategist>(StrategToSpawn);
    if (NewObj) {
        NewObj->SetActorLocation(UE_coordinates);
        NewObj->SetActorRotation(FRotator::ZeroRotator);
    } else {
        UE_LOG(LogTemp, Warning, TEXT("cannot spawn strategist"));
        return TOptional<AStrategist*>();
    }
    return TOptional<AStrategist*>(NewObj);
}