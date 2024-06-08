// Fill out your copyright notice in the Description page of Project Settings.


#include "MyJsonComponent.h"
//#include "Serialization/JsonSerializer.h"

// Sets default values for this component's properties
UMyJsonComponent::UMyJsonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Http = &FHttpModule::Get();
}


// Called when the game starts
void UMyJsonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyJsonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyJsonComponent::fLoadJson()
{
	bool bOk = true;

	FString fileName = "Player.json";
	FString fullPathContent = FPaths::ProjectConfigDir() + fileName;
	FString jsonStr;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*fullPathContent)) {
		bOk = false;
	}

	if (bOk) {
		FFileHelper::LoadFileToString(jsonStr, *fullPathContent);

		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(jsonStr);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

		FJsonSerializer::Deserialize(JsonReader, JsonObject);
		TSharedPtr<FJsonObject> player = JsonObject->GetObjectField("player");

		this->playerStruct.name = player->GetStringField("name");
		this->playerStruct.score = player->GetIntegerField("score");
	}
}

FString UMyJsonComponent::fPrintPlayerStruct(FPlayerStruct p)
{
	FString resp = "";
	resp += "name: " + p.name + "\r\n";
	resp += "score: " + FString::FromInt(p.score) + "\r\n";
	return resp;
}

void UMyJsonComponent::HttpLoggin(FString loggin, FString password)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", loggin);
	RequestObj->SetStringField("password", password);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMyJsonComponent::HttpRecerve);
	Request->SetURL("127.0.0.1:18080/register");
	Request->SetVerb("POST");
	Request->SetContentAsString(RequestBody);

	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->ProcessRequest();
}

void UMyJsonComponent::HttpRegister(FString loggin, FString password)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", loggin);
	RequestObj->SetStringField("password", password);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMyJsonComponent::HttpRecerve);
	Request->SetURL("127.0.0.1:18080/register");
	Request->SetVerb("POST");
	Request->SetContentAsString(RequestBody);

	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->ProcessRequest();
}

void UMyJsonComponent::HttpSendPlayer(FPlayerStruct player)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("name", player.name);
	RequestObj->SetNumberField("score", player.score);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UMyJsonComponent::HttpRecerve);
	Request->SetURL("127.0.0.1:18080/gotStats");
	Request->SetVerb("POST");
	Request->SetContentAsString(RequestBody);

	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->ProcessRequest();

}

void UMyJsonComponent::HttpGetCall()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UMyJsonComponent::HttpRecerve);

	Request->SetURL("127.0.0.1:18080/gotStats");
	Request->SetVerb("GET");

	// Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	// Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->ProcessRequest();
}

void UMyJsonComponent::HttpRecerve(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bOutSuccess)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);
	// ResponseObj->GetStringField("name");
	// ResponseObj->GetIntegerField("score");

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(Response->GetContentAsString()));
}