// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MyJsonComponent.h"
#include "JsonObjectConverter.h"

#include "Blueprint/UserWidget.h"
#include "MyMenuWidget.generated.h"

UCLASS()
class VOEVODA_API UMyMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	FHttpModule* Http;
public:
	
	UFUNCTION(BlueprintCallable, Category = "HttpRequest")
		void CallLogin(FString login, FString password);
	UFUNCTION(BlueprintCallable, Category = "HttpRequest")
		void CallRegister(FString login, FString password);

	void HttpRecerve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bOutSuccess);
};
