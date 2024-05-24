#include "GameWorld.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

AGameWorld::AGameWorld() {

    SupplyArmyInteractorInstance = SupplyArmyInteractor();
    PrimaryActorTick.bCanEverTick = true;

}
AGameWorld::~AGameWorld() {

}
void AGameWorld::Tick(float DeltaTime) {

    Super::Tick(DeltaTime);

    if (SupplyArmyInteractorInstance.is_seted()) {
        //SupplyArmyInteractorInstance.StartSupplyArmyEvent(strategists, structures, GetWorld()->GetTimeSeconds());
        SupplyArmyInteractorInstance.StartSupplyArmyEvent2(strategists, structures);
    }
    //FString message = FString::Printf(TEXT("x: %d, y: %d"), playerCharacter->Strategist->general.position.x, playerCharacter->Strategist->general.position.y);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
    //if (!SupplyArmyInteractorInstance.is_seted()) {
    //    return;
    //}
    //
    //for (AStructure* structure : structures) {
    //    for (AStrategist* strategist : strategists) {
    //        SupplyArmyInteractorInstance.StartSupplyArmyEvent2(strategist, structure);
    //    }
    //}
}

void AGameWorld::InitializePointers() {

    for (TActorIterator<AMapPainter> ActorItr(GetWorld()); ActorItr;
        ++ActorItr) {
        painter_ptr = Cast<AMapPainter>(*ActorItr);
        map_ptr = &(painter_ptr->map);
    }

    for (TActorIterator<AMyPlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        playerCharacter = Cast<AMyPlayerCharacter>(*ActorItr);
    }

}

void AGameWorld::BeginPlay() {
    Super::BeginPlay();

    InitializePointers();
    painter_ptr->BeginPlayFunction();


    if (painter_ptr) {
        for (int32 id = 1;  id <= map_ptr->GeneralsInitPos.Num(); id++){
            auto general_pos = map_ptr->GeneralsInitPos[id-1];
            AStrategist* Strategist = NewObject<AStrategist>(this);
            Strategist->id = id;
            Strategist->general.position = general_pos;
            strategists.Add(Strategist);
        }
        for (int32 id = 1; id <= map_ptr->GeneralsInitPos.Num(); id++) {
            City* new_city = NewObject<City>(this);
            new_city->SetOwnerPosition(strategists[id-1], map_ptr->CitiesInitPos[id-1], id);
            strategists[id-1]->addStructure(new_city->id);
            structures.Add(new_city);
        }
        for (int32 id = map_ptr->GeneralsInitPos.Num()+1; id <= map_ptr->CitiesInitPos.Num(); id++) {
            int32 randomStrategist = FMath::RandRange(0, map_ptr->GeneralsInitPos.Num() - 1);
            City* new_city = NewObject<City>(this);
            new_city->SetOwnerPosition(strategists[randomStrategist], map_ptr->CitiesInitPos[id-1], id);
            strategists[randomStrategist]->addStructure(new_city->id);
            structures.Add(new_city);
        }
    }

    else {
        UE_LOG(LogTemp, Warning, TEXT("painter_ptr is nullptr."));
    }

    for (AStructure* structure : structures) {
        for (AStrategist* strategist : strategists) {
            FString message = FString::Printf(TEXT("strategist: %d, structure: %d"), strategist->id, structure->id);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
        }
    }

    if (playerCharacter) {

        playerCharacter->InitializeStrategist();
        SupplyArmyInteractorInstance.SetMapAndPlayerCharacter(playerCharacter, strategists, structures);

        //AStrategist new_strategist(playerCharacter->Strategist);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("playerCharacter is nullptr."));
    }

    FString message = FString::Printf(TEXT("Strategists size: %d, Structures size: %d"), strategists.Num(), structures.Num());
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
    FString message2= FString::Printf(TEXT("x: %d, y: %d"),playerCharacter->Strategist->general.position.x, playerCharacter->Strategist->general.position.y);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message2);
}

