// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Strategist.h"
#include "AI_ArmyWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class VOEVODA_API UAI_ArmyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Reference")
		AStrategist* StrategistRef;
	void SetOwner(AStrategist* owner_ptr) { StrategistRef = owner_ptr; }
};
