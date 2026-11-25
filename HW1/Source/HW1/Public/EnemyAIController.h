#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

class UBehaviorTree;

UCLASS()
class HW1_API AEnemyAIController : public AAIController
{
  GENERATED_BODY()

public:
  AEnemyAIController();

protected:
  virtual void OnPossess(APawn* InPawn) override;

  UPROPERTY(EditDefaultsOnly, Category = "AI")
  UBehaviorTree* BehaviorTreeAsset;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
  UAIPerceptionComponent* PerceptionComp;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
  UAISenseConfig_Sight* SightConfig;

  UFUNCTION()
  void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};