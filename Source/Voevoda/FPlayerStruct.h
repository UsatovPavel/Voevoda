#pragma once

#include "CoreMinimal.h"

#include "FPlayerStatsStruct.h"

#include "FPlayerStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStruct")
	FString name = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStruct")
	int32 score = 0;
};