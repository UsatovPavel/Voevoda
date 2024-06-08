// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "JsonObjectConverter.h"
#include "Http.h"

#include "FPlayerStruct.h"

#include "MyJsonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOEVODA_API UMyJsonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyJsonComponent();

	FHttpModule* Http;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JsonComponent")
	FPlayerStruct playerStruct;
	UFUNCTION(BlueprintCallable, Category = "JsonComponent")
	void fLoadJson();
	UFUNCTION(BlueprintCallable, Category = "JsonComponent")
	FString fPrintPlayerStruct(FPlayerStruct p);
	UFUNCTION(BlueprintCallable, Category = "HttpRequest")
	void HttpLoggin(FString loggin, FString password);
	UFUNCTION(BlueprintCallable, Category = "HttpRequest")
	void HttpRegister(FString loggin, FString password);

	UFUNCTION(BlueprintCallable, Category = "HttpRequest")
	void HttpSendPlayer(FPlayerStruct player);
	UFUNCTION(BlueprintCallable, Category = "HttpRequest")
	void HttpGetCall();

	void HttpRecerve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bOutSuccess);
};
