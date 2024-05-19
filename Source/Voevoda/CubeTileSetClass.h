// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeTileSetClass.generated.h"

class UStaticMeshComponent;

UCLASS()
class VOEVODA_API ACubeTileSetClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeTileSetClass();
protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TileMesh;
};
