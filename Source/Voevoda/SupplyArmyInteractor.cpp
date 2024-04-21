#include "SupplyArmyInteractor.h"
#include "HAL/PlatformProcess.h"


uint32 FSupplyArmyInteractor::Run()
{
    City* city = Cast<City>(CurrentStructure);
    
    if (!city) {
        return 0;
    }
    for (int i = 0; i < 6; ++i) {

        FPlatformProcess::Sleep(0.5f);
  
        if (CurrentStrategist->general.position != city->position) {
            return 0;
        }
    }

    FScopeLock ScopeLock(&GetMutex());
    city->replenish_army(CurrentStrategist);
 

    return 0;
}


FSupplyArmyInteractor::FSupplyArmyInteractor(AStrategist* Strategist, AStructure* Structure): CurrentStrategist(Strategist),
CurrentStructure(Structure){}

FSupplyArmyInteractor::~FSupplyArmyInteractor()
{
   /* for (auto& Elem : GetActiveThreads())
    {
        Elem.Value.Key->Kill(true);
        delete Elem.Value.Key;
        delete Elem.Value.Value;
    }
    GetActiveThreads().Empty();*/
}

void FSupplyArmyInteractor::StartSupplyArmyEvent(AStrategist* Strategist, AStructure* Structure)
{
    TPair<int32, int32> Pair = TPair<int32, int32>(Strategist->id, Structure->id);

    // need to replace with condition ThreadCompleted
    if (!GetActiveThreads().Contains(Pair))
    {
        FSupplyArmyInteractor* Interactor = new FSupplyArmyInteractor(Strategist, Structure);
        FRunnableThread* Thread = FRunnableThread::Create(Interactor, TEXT("SupplyArmyInteractorThread"));
        GetActiveThreads().Add(Pair, TPair<FRunnableThread*, FSupplyArmyInteractor*>(Thread, Interactor));
    }
}

//void FSupplyArmyInteractor::CleanupFinishedThreads()
//{
//    for (auto It = GetActiveThreads().CreateIterator(); It; ++It)
//    {
//        /*if (It.Value()->GetThreadCompleted())
//        {
//            It.Value()->Kill(true);
//            delete It.Value();
//            It.RemoveCurrent();
//        }*/
//    }
//}
