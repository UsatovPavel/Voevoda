// Fill out your copyright notice in the Description page of Project Settings.


#include "Structure.h"

// Sets default values
AStructure::AStructure(Location init_pos): position(init_pos), capasity(FMath::RandRange(50, 100)), manpower_growth(FMath::RandRange(0, 5))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
AStructure::AStructure() :AStructure(Location(0, 0)) {}
// Called when the game starts or when spawned
void AStructure::BeginPlay()
{
	Super::BeginPlay();
	const FVector location = GetActorLocation();
	const FRotator rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, location, rotation);
}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

