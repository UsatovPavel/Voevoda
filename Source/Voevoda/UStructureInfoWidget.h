#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UStructureInfoWidget.generated.h"

UCLASS()
class VOEVODA_API UUStructureInfoWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Function to update the widget with the properties of the structure
    void UpdateWidget(int32 id, int32 manpower_growth);

protected:
    // Text widgets to display the properties of the structure
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* IDText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ManpowerGrowthText;
};
