#pragma once

#include "Strategist.h"
#include "Structure.h"
#include "City.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "HAL/RunnableThread.h"
#include "Misc/ScopeLock.h"

class VOEVODA_API FSupplyArmyInteractor : public FRunnable
{
private:
    AStrategist* CurrentStrategist;
    AStructure* CurrentStructure;

public:
    //static FCriticalSection Mutex;
    //static TMap<TPair<int32, int32>, TPair<FRunnableThread*, FSupplyArmyInteractor*>> ActiveThreads;

    static FCriticalSection& GetMutex() {
        static FCriticalSection Mutex;
        return Mutex;
    }

    static TMap<TPair<int32, int32>, TPair<FRunnableThread*, FSupplyArmyInteractor*>>& GetActiveThreads() {
        static TMap<TPair<int32, int32>, TPair<FRunnableThread*, FSupplyArmyInteractor*>> ActiveThreads;
        return ActiveThreads;
    }

    static void StartSupplyArmyEvent(AStrategist* InStrategist, AStructure* InStructure);

    FSupplyArmyInteractor(AStrategist* Strategist, AStructure* Structure);

    ~FSupplyArmyInteractor();

    virtual uint32 Run() override;

    //void CleanupFinishedThreads();
};