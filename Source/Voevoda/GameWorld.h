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
#include "SupplyArmyInteractor.h"
#include "Army.h"
#include "TerrainType.h"
#include "GameMap.h"
#include "MapPainter.h"
#include "Strategist.h"
#include "Structure.h"
#include "City.h"
#include "SupplyArmyInteractor.h"
#include "MyPlayerCharacter.h"
#include "GameWorld.generated.h"


UCLASS()
class VOEVODA_API AGameWorld : public AActor {
    GENERATED_BODY()

public:
    AGameWorld();
    virtual void Tick(float DeltaTime) override;

public:
    virtual void BeginPlay() override;

private:
    GameMap* map_ptr;
    AMapPainter* painter_ptr;
    UPROPERTY()
    TArray<AStructure*> structures;
    AMyPlayerCharacter* player_ptr;
    SupplyArmyInteractor SupplyArmyInteractorInstance;
    TOptional<AStrategist*> spawn_strategist(FVector UE_coordinates);
public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
        TArray<AStrategist*> strategists;
    UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
        void print_generals_pos();
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = True), Category = "Setup")
        TSubclassOf<AActor> BP_Strategist;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bool")
        bool is_losed = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bool")
        bool is_victory = false;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Bool")
        bool is_spawn_completed = false;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Bool")
        bool is_set_ref_completed = false;
    UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
        void set_ref_processed() {
        is_set_ref_completed = true;
    }
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Bool")
        bool is_new_step = false;
    UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
        void new_step_processed() {
        is_new_step = false;
    }
    void spawn_objects();
    float time_last_move = 0;
};
