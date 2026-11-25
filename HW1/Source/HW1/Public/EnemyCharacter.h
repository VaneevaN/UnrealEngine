#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class HW1_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:

    AEnemyCharacter();

protected:

    virtual void BeginPlay() override;

};
