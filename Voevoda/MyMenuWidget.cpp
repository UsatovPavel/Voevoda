// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMenuWidget.h"

void UMyMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Http = &FHttpModule::Get();
}

void UMyMenuWidget::CallLogin(FString login, FString password)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", login);
	RequestObj->SetStringField("password", password);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMyMenuWidget::HttpRecerve);
	Request->SetURL("127.0.0.1:18080/login");
	Request->SetVerb("POST");
	Request->SetContentAsString(RequestBody);

	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->ProcessRequest();
}

void UMyMenuWidget::CallRegister(FString login, FString password)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", login);
	RequestObj->SetStringField("password", password);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMyMenuWidget::HttpRecerve);
	Request->SetURL("127.0.0.1:18080/register");
	Request->SetVerb("POST");
	Request->SetContentAsString(RequestBody);

	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->ProcessRequest();
}

void UMyMenuWidget::HttpRecerve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bOutSuccess)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);
	// ResponseObj->GetStringField("name");
	// ResponseObj->GetIntegerField("score");

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(Response->GetContentAsString()));
}
