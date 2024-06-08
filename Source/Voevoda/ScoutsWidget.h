// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoutsWidget.generated.h"

/**
 * 
 */
UCLASS()
class VOEVODA_API UScoutsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateWidgetScoutsNumber(int32 ScoutsNumber);
	void UpdateWidgetSend( bool send);


protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoutsNumberText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MessageText;
	
};
