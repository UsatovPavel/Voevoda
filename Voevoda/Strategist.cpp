// Fill out your copyright notice in the Description page of Project Settings.


#include "Strategist.h"
#include "Components/WidgetComponent.h"
#include "Math/Vector.h"
#include "AI_ArmyWidget.h"
// Sets default values
AStrategist::AStrategist()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//User_near = true;

}
AStrategist::AStrategist(Location init_loc) :AStrategist() {
	general.position = init_loc;
	manpower_available = FMath::RandRange(100, 300);
	general = General();
}

// Called when the game starts or when spawned
void AStrategist::BeginPlay()
{
	Super::BeginPlay();
	const FVector location = GetActorLocation();
	const FRotator rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, location, rotation);
	//ArmyWidgetComp = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("ArmyBar"));
	//ArmyWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	/*
	FObjectInitializer ObjectInitializer;
	if (RootComponent == nullptr) {
		RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Root"));
	}
	ArmyWidgetComp = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("ArmyBar"));
	ArmyWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	if (ArmyWidgetComp->GetUserWidgetObject() != nullptr) {

		UAI_ArmyWidget* ArmyBar = Cast<UAI_ArmyWidget>(ArmyWidgetComp->GetUserWidgetObject());
		ArmyBar->SetOwner(this);
	}остановился на том что летит на конструкторе(41 строка).
	*/
}

// Called every frame
void AStrategist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	general.update_pos(this->GetActorLocation());
}

