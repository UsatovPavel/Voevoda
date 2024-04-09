// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategist.h"

// Sets default values
AStrategist::AStrategist()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
AStrategist::AStrategist(Location init_loc):AStrategist() {
	general.position = init_loc;
}

// Called when the game starts or when spawned
void AStrategist::BeginPlay()
{
	Super::BeginPlay();
	const FVector location = GetActorLocation();
	const FRotator rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, location, rotation);
}

// Called every frame
void AStrategist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

