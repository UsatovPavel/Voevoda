// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/UnrealString.h"
#include "Containers/Array.h"
#include "TerrainType.h"
#include "General.h"
#include "Scout.h"
#include "PlayerGameSessionStatistic.h"
#include "Strategist.generated.h"

UCLASS()
class MYPROJECT1040_API AStrategist : public AActor
{
	GENERATED_BODY()
private:
	bool dead;
public:	
	int32 id;
	FString username;
	TArray<int32> structures_controlled;
	int32 manpower_available;
	TArray<TArray<TerrainType>> visited_tiles;
	General general;
	TArray<Scout> scouts;
	PlayerGameSessionStatistic session_stats;
	bool is_dead() {
		return dead;
	}
	AStrategist();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
