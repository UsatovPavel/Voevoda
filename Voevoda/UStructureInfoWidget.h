// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "City.h"
#include "Blueprint/UserWidget.h"
#include "UStructureInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class VOEVODA_API UUStructureInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // Function to update the widget with the properties of the structure
    void UpdateWidget(int32 id, int32 manpower_growth, UnitType Type);
    void PlayerStepOnStructure(int32 id, int32 manpower_growth, UnitType Type);
    void PlayerMovedFromStructure();
    void AfterCityreplenish(int32 manpower_growth);
    int32 GetManpowerGrowthWantToSpend();

    // Custom function to handle input from the player
    UFUNCTION(BlueprintCallable, Category = "Custom")
    void HandleInputEvent(const FText& EnteredText);
    
    void ToViewport();
    void FromViewport();



protected:
    // Text widgets to display the properties of the structure
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* IDText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ManpowerGrowthText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* UnitTypeText;

    /* UPROPERTY(meta = (BindWidget))
     class UTextBlock* HintTextForInput;*/

    int32 ManpowerGrowthWantToSpend = 0;
    bool OnViewport = 0;
};
