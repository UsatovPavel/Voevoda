// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStrategist.h"
#include "UStructureInfoWidget.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

UCLASS(Blueprintable)
class AMyPlayerCharacter : public ACharacter, public BaseStrategist {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  AMyPlayerCharacter();

  // Returns TopDownCameraComponent subobject
  FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComp; }
  // Returns CameraBoom subobject
  FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArmComp; }
  // Returns CursorToWorld subobject
  FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

  UFUNCTION()
  void SetSelected();
  UFUNCTION()
  void SetDeselected();
  
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  //virtual void SetupPlayerInputComponent(
  //	class UInputComponent *PlayerInputComponent) override;

  // Player position
  // UPROPERTY(EditAnywhere)
  // FVector position = FVector(0, 0, 0);

  UPROPERTY(EditDefaultsOnly, Category = "UI")
  TSubclassOf<class UUStructureInfoWidget> HUDWidgetClass;

  UPROPERTY()
  UUStructureInfoWidget* SupplyArmyWidget = nullptr;

protected:
	virtual void BeginPlay() override;
  // Set camera
  UPROPERTY(EditAnywhere)
  class UCameraComponent *CameraComp;
  // camera boom
  UPROPERTY(EditAnywhere)
  class USpringArmComponent *SpringArmComp;
  // A decal that projects to the cursor location
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UDecalComponent* CursorToWorld;

  // Set movement
  // void MoveForward(float InputValue);
  // void MoveRight(float InputValue);

  UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
	  int32 GetInfantry() {
	  return general.army_size.Infantry;
  }
  UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
	  int32 GetArchers() {
	  return general.army_size.Archers;
  }
  UFUNCTION(BlueprintCallable, Category = "UFUNCTION")
	  int32 GetCavalry() {
	  return general.army_size.Cavalry;
  }
};
