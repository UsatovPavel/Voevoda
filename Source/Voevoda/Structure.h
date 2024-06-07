// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Location.h"
#include "Strategist.h"
#include "Math/UnrealMathUtility.h"
#include "Structure.generated.h"
UCLASS()
class VOEVODA_API AStructure : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> ActorToSpawn;
public:	
	// Sets default values for this actor's properties
	AStructure(Location init_pos);
	AStructure();
	 Location position; //if const need Constructor()->problems with "Structure.generated.h"
	 int32 capasity;
	 int32 manpower_growth;
	 int32 id;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
