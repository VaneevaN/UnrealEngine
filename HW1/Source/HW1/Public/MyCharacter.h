#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractSignature);

UCLASS()
class HW1_API AMyCharacter : public ACharacter
{
  GENERATED_BODY()

public:
  AMyCharacter();

  virtual void Tick(float DeltaTime) override;
  virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
  TObjectPtr<UInputAction> SprintAction;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
  TObjectPtr<UInputAction> InteractAction;

  UPROPERTY(BlueprintAssignable, Category = "Interaction")
  FOnInteractSignature OnInteract;

  UPROPERTY(BlueprintReadOnly, Category = "Movement")
  bool bIsSprinting = false;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
  float SprintSpeed = 800.f;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
  float MaxStamina = 100.f;

  UPROPERTY(BlueprintReadOnly, Category = "Stamina")
  float Stamina = 100.f;

  UPROPERTY(EditAnywhere, Category = "Stamina")
  float StaminaDrainPerSecond = 20.f;

  UPROPERTY(EditAnywhere, Category = "Stamina")
  float StaminaRegenPerSecond = 10.f;

  UPROPERTY(EditAnywhere, Category = "Stamina")
  float MinStaminaToSprint = 15.f;

protected:
  virtual void BeginPlay() override;

  void StartSprint();
  void StopSprint();
  void Interact();
  void SetSprinting(bool bNewSprinting);

private:
  float DefaultWalkSpeed = 500.f;
  bool bWantsToSprint = false;
};