// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoutsWidget.h"
#include "Components/TextBlock.h"

void  UScoutsWidget::UpdateWidgetScoutsNumber(int32 ScoutsNumber) {

    if (ScoutsNumberText)
    {
        ScoutsNumberText->SetText(FText::FromString(FString::Printf(TEXT("Scouts Number: %d"), ScoutsNumber)));
    }

}
void  UScoutsWidget::UpdateWidgetSend(bool send) {
    if (MessageText && send)
    {
        MessageText->SetText(FText::FromString(FString::Printf(TEXT(""))));
    }
    else if (MessageText) {
        MessageText->SetText(FText::FromString(FString::Printf(TEXT("do not have scouts"))));
    }
}