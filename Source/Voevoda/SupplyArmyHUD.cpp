// Fill out your copyright notice in the Description page of Project Settings.


#include "SupplyArmyHUD.h"
#include "Blueprint/UserWidget.h"
//
//void ASupplyArmyHUD::DrawHUD()
//{
//    Super::DrawHUD();
//
//    // Check if the current strategist's ID is 0
//    if (true)
//    {
//        // Create or update the UserWidget
//        if (!CurrentWidget)
//        {
//            CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
//            if (CurrentWidget)
//            {
//                CurrentWidget->AddToViewport();
//            }
//        }
//    }
//    else
//    {
//        // Hide the UserWidget
//        if (CurrentWidget)
//        {
//            CurrentWidget->RemoveFromViewport();
//            CurrentWidget = nullptr;
//        }
//    }
//}
// 
ASupplyArmyHUD::ASupplyArmyHUD() {
    ConstructorHelpers::FClassFinder<UUserWidget> UUStructureInfoWidget(TEXT("/Game/BluePrints/SupplyArmyWidget"));
    HUDWidgetClass = UUStructureInfoWidget.Class;
}
void ASupplyArmyHUD::BeginPlay()
{
    Super::BeginPlay();

    if (HUDWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        CurrentWidget->AddToViewport();
    }

    if (CurrentWidget)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Widget is created!"));
        CurrentWidget->AddToViewport();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Widget is not created!"));
    }
}

void ASupplyArmyHUD::DisplayHUD()
{
    if (CurrentWidget)
    {
        CurrentWidget->AddToViewport();
    }
}

void ASupplyArmyHUD::HideHUD()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromViewport();
    }
}

