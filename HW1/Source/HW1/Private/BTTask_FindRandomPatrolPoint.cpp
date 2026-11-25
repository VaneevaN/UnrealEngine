#include "BTTask_FindRandomPatrolPoint.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRandomPatrolPoint::UBTTask_FindRandomPatrolPoint()
{
  NodeName = TEXT("Find Random Patrol Point");

  BlackboardKey.AddVectorFilter(
    this,
    GET_MEMBER_NAME_CHECKED(
      UBTTask_FindRandomPatrolPoint,
      BlackboardKey
    )
  );
}

EBTNodeResult::Type UBTTask_FindRandomPatrolPoint::ExecuteTask(
  UBehaviorTreeComponent& OwnerComp,
  uint8* NodeMemory
)
{
  AAIController* AIController = OwnerComp.GetAIOwner();

  if (!AIController)
  {
    return EBTNodeResult::Failed;
  }

  APawn* ControlledPawn = AIController->GetPawn();

  if (!ControlledPawn)
  {
    return EBTNodeResult::Failed;
  }

  UNavigationSystemV1* NavSystem =
    FNavigationSystem::GetCurrent<UNavigationSystemV1>(
      ControlledPawn->GetWorld()
    );

  if (!NavSystem)
  {
    return EBTNodeResult::Failed;
  }

  const FVector Origin = ControlledPawn->GetActorLocation();

  FNavLocation RandomLocation;

  const bool bFoundLocation =
    NavSystem->GetRandomReachablePointInRadius(
      Origin,
      SearchRadius,
      RandomLocation
    );

  if (!bFoundLocation)
  {
    return EBTNodeResult::Failed;
  }

  UBlackboardComponent* Blackboard =
    OwnerComp.GetBlackboardComponent();

  if (!Blackboard)
  {
    return EBTNodeResult::Failed;
  }

  Blackboard->SetValueAsVector(
    BlackboardKey.SelectedKeyName,
    RandomLocation.Location
  );

  return EBTNodeResult::Succeeded;
}
