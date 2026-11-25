#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyAIController::AEnemyAIController()
{
  PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
  SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

  SightConfig->SightRadius = 1500.0f;
  SightConfig->LoseSightRadius = 2000.0f;
  SightConfig->PeripheralVisionAngleDegrees = 60.0f;
  SightConfig->SetMaxAge(5.0f);

  SightConfig->DetectionByAffiliation.bDetectEnemies = true;
  SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
  SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

  PerceptionComp->ConfigureSense(*SightConfig);
  PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

  PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
  Super::OnPossess(InPawn);

  if (BehaviorTreeAsset)
  {
    RunBehaviorTree(BehaviorTreeAsset);
  }

  if (ACharacter* MyCharacter = Cast<ACharacter>(InPawn))
  {
    if (UCharacterMovementComponent* MoveComp = MyCharacter->GetCharacterMovement())
    {
      MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
      MoveComp->GravityScale = 1.0f;
    }
  }
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
  UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

  if (BlackboardComp)
  {
    if (Stimulus.WasSuccessfullySensed())
    {
      BlackboardComp->SetValueAsObject("TargetActor", Actor);
      BlackboardComp->SetValueAsBool("CanSeePlayer", true);
    }
    else
    {
      BlackboardComp->ClearValue("TargetActor");
      BlackboardComp->SetValueAsBool("CanSeePlayer", false);
    }
  }
}