// Fill out your copyright notice in the Description page of Project Settings.


#include "UStructureInfoWidget.h"

#include "Components/TextBlock.h"

void UUStructureInfoWidget::UpdateWidget(int32 id, int32 manpower_growth, UnitType Type)
{
    if (IDText)
    {
        IDText->SetText(FText::FromString(FString::Printf(TEXT("ID: %d"), id)));
    }

    if (ManpowerGrowthText)
    {
        ManpowerGrowthText->SetText(FText::FromString(FString::Printf(TEXT("Units number: %d"), manpower_growth)));
    }


    switch (Type) {
    case Archers:
        if (UnitTypeText) {
            UnitTypeText->SetText(FText::FromString(FString::Printf(TEXT("UnitType: Archers"))));
        }
        break;
    case Infantry:
        if (UnitTypeText) {
            UnitTypeText->SetText(FText::FromString(FString::Printf(TEXT("UnitType: Infantry"))));
        }
        break;
    case Cavalry:
        if (UnitTypeText) {
            UnitTypeText->SetText(FText::FromString(FString::Printf(TEXT("UnitType: Cavalry"))));
        }
        break;
    }
}



void  UUStructureInfoWidget::PlayerStepOnStructure(int32 id, int32 manpower_growth, UnitType Type) {
    UpdateWidget(id, manpower_growth, Type);
    ToViewport();
    //AddToViewport();
}

int32 UUStructureInfoWidget::GetManpowerGrowthWantToSpend() {
    return ManpowerGrowthWantToSpend;
}

void UUStructureInfoWidget::PlayerMovedFromStructure() {
    //RemoveFromViewport();
    FromViewport();
    ManpowerGrowthWantToSpend = 0;
}

void UUStructureInfoWidget::ToViewport() {
    if (!OnViewport) {
        AddToViewport();
        OnViewport = true;
    }

}
void UUStructureInfoWidget::FromViewport() {
    if (OnViewport) {
        RemoveFromViewport();
        OnViewport = false;
    }
}

void UUStructureInfoWidget::AfterCityreplenish(int32 manpower_growth) {
    if (ManpowerGrowthText)
    {
        ManpowerGrowthText->SetText(FText::FromString(FString::Printf(TEXT("Units number: %d"), manpower_growth)));
    }
    ManpowerGrowthWantToSpend = 0;
}

void UUStructureInfoWidget::HandleInputEvent(const FText& EnteredText)
{
    ManpowerGrowthWantToSpend = FCString::Atoi(*EnteredText.ToString());

}