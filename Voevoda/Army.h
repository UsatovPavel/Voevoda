// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/IntVector.h"
/**
 *
 */
class ArmyModifier {
public:
	float Archers = 100;
	float Infantry = 100;
	float Cavalry = 100;
	ArmyModifier(float x, float y, float z) : Archers(x), Infantry(y), Cavalry(z) {}
	ArmyModifier operator *(const float coef) {
		return ArmyModifier(Archers * coef, Infantry * coef, Cavalry * coef);
	}
	ArmyModifier operator +=(const ArmyModifier other) {
		Archers += other.Archers;
		Infantry += other.Infantry;
		Cavalry += other.Cavalry;
		return *this;
	}
	ArmyModifier operator * (const ArmyModifier other) {
		ArmyModifier result(0, 0, 0);
		result.Archers = (Archers / 100 * other.Archers);
		result.Cavalry = (Cavalry / 100 * other.Cavalry);
		result.Infantry = (Infantry / 100 * other.Infantry);
		return result;
	}
};
class VOEVODA_API Army
{
public:
	FIntVector MakeIntVector() {
		return { Archers, Infantry, Cavalry };
	}
	int32 Archers;
	int32 Infantry;
	int32 Cavalry;
	Army() :Archers(FMath::RandRange(0, 10)), Infantry(FMath::RandRange(0, 10)), Cavalry(FMath::RandRange(0, 10)) {}
	void rand(int32 RandomSeed) {
		FRandomStream SRand = FRandomStream();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("from Army.rand() %lld"), RandomSeed));
		SRand.Initialize(RandomSeed);
		Archers = SRand.FRandRange(0, 10); Infantry = SRand.FRandRange(0, 10); Cavalry = SRand.FRandRange(0, 10);
	}
	Army(int32 Arch, int32 Inf, int32 Cav) :Archers(Arch), Infantry(Inf), Cavalry(Cav) {}
	Army operator +=(Army other) {
		Archers += other.Archers;
		Infantry += other.Infantry;
		Cavalry += other.Cavalry;
		return *this;
	}
	Army operator*(int32 coef) {
		return Army(Archers * coef, Infantry * coef, Cavalry * coef);
	}
	float calculate_strength(ArmyModifier x) {
		return x.Archers * Archers + x.Infantry * Infantry + x.Cavalry * Cavalry;
	}
};
class ArmyComposition {
public:
	float Arch;
	float Inf;
	float Cav;
	ArmyComposition(Army army) {
		Arch = static_cast<float>(army.Archers) / (army.Archers + army.Cavalry + army.Infantry);
		Inf = static_cast<float>(army.Infantry) / (army.Archers + army.Cavalry + army.Infantry);
		Cav = static_cast<float>(army.Cavalry) / (army.Archers + army.Cavalry + army.Infantry);
	}
};
