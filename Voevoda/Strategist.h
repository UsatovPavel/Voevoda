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
class VOEVODA_API AStrategist : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
		TSubclassOf<AActor> ActorToSpawn;
	//UPROPERTY(VisibleAnywhere)
	//	class UWidgetComponent* ArmyWidgetComp;
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
	Location get_location() {
		return general.position;
	}
	AStrategist();
	AStrategist(Location init_loc);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
		int32 GetInfantry() {
		return general.army_size.Infantry;
	}
	UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
		int32 GetArchers() {
		return general.army_size.Archers;
	}
	UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
		int32 GetCavalry() {
		return general.army_size.Cavalry;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
		bool User_near = false;
	UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
		FVector GetLocation() {
		return general.position.UE_coordinates();
	}
	UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
		void PrintPosition() {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("position in BP %d %d"), general.position.X, general.position.Y));
	}
	//UPROPERTY(VisibleAnywhere)
	//	class UWidgetComponent* ArmyWidgetComp;
};
