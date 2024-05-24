#include "UStructureInfoWidget.h"
#include "Components/TextBlock.h"

void UUStructureInfoWidget::UpdateWidget(int32 id, int32 manpower_growth)
{
    if (IDText)
    {
        IDText->SetText(FText::FromString(FString::Printf(TEXT("ID: %d"), id)));
    }

    if (ManpowerGrowthText)
    {
        ManpowerGrowthText->SetText(FText::FromString(FString::Printf(TEXT("Manpower Growth: %d"), manpower_growth)));
    }
}
