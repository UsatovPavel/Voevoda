// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Actor.h"
#include "PaperTileLayer.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "Army.h"
#include "City.h"
#include "SupplyArmyInteractor.h"
#include "TerrainType.h"
#include "GameMap.h"
#include "MapPainter.h"
#include "Strategist.h"
#include "Structure.h"
#include "GameWorld.generated.h"

UCLASS()
class VOEVODA_API AGameWorld : public AActor {
    GENERATED_BODY()

public:
    AGameWorld();
    ~AGameWorld();
    virtual void Tick(float DeltaTime) override;

public:
    virtual void BeginPlay() override;

private:
    // UPROPERTY(EditAnywhere, Category = "TileMap")
    GameMap* map_ptr;
    AMapPainter* painter_ptr;
    TArray<AStrategist*> strategists;
    TArray<AStructure*> structures;
    SupplyArmyInteractor SupplyArmyInteractorInstance;
    AMyPlayerCharacter* playerCharacter;

    void InitializePointers();
};
