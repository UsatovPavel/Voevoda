// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UStructureInfoWidget.h"
#include "SupplyArmyHUD.generated.h"

/**
 * 
 */
UCLASS()
class VOEVODA_API ASupplyArmyHUD : public AHUD
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;
 
     void DisplayHUD();

     ASupplyArmyHUD();

     ~ASupplyArmyHUD() = default;

    void HideHUD();
  //  virtual void DrawHUD() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    UUserWidget* CurrentWidget = nullptr;



	
};
//UUStructureInfoWidget* CurrentWidget = CreateWidget<UUStructureInfoWidget>(GetWorld(), UUStructureInfoWidget::StaticClass());