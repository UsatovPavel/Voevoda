#pragma once

#include "CoreMinimal.h"

#include "FPlayerStatsStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStatsStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStatsStruct")
	int32 id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStatsStruct")
	FString name = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStatsStruct")
	int32 count = 0;
};