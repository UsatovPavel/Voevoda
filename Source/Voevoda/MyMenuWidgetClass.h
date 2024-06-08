// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MyJsonComponent.h"

#include "MyMenuWidgetClass.generated.h"

/**
 * 
 */
UCLASS()
class VOEVODA_API UMyMenuWidgetClass : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClass")
	UMyJsonComponent* myJsonComponent;
};
