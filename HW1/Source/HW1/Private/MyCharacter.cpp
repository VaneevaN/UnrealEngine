#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Engine/Engine.h"

AMyCharacter::AMyCharacter()
{
  PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::BeginPlay()
{
  Super::BeginPlay();
  DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
  Stamina = MaxStamina;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
  {
	if (SprintAction)
	{
	  EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &AMyCharacter::StartSprint);
	  EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMyCharacter::StopSprint);
	  EIC->BindAction(SprintAction, ETriggerEvent::Canceled, this, &AMyCharacter::StopSprint);
	}
	if (InteractAction)
	{
	  EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::Interact);
	}
  }
}

void AMyCharacter::StartSprint()
{
  bWantsToSprint = true;
}

void AMyCharacter::StopSprint()
{
  bWantsToSprint = false;
  SetSprinting(false);
}

void AMyCharacter::Interact()
{
  OnInteract.Broadcast();
}

void AMyCharacter::SetSprinting(bool bNewSprinting)
{
  bIsSprinting = bNewSprinting;
  GetCharacterMovement()->MaxWalkSpeed = bNewSprinting ? SprintSpeed : DefaultWalkSpeed;
}

void AMyCharacter::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (bWantsToSprint && !bIsSprinting && Stamina >= MinStaminaToSprint)
  {
	SetSprinting(true);
  }

  if (bIsSprinting)
  {
	const bool bMoving = GetVelocity().SizeSquared2D() > 1.f;
	if (bMoving)
	{
	  Stamina = FMath::Max(0.f, Stamina - StaminaDrainPerSecond * DeltaTime);
	}
	if (Stamina <= 0.f)
	{
	  bWantsToSprint = false;
	  SetSprinting(false);
	}
  }
  else
  {
	Stamina = FMath::Min(MaxStamina, Stamina + StaminaRegenPerSecond * DeltaTime);
  }

  if (GEngine)
  {
	GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Yellow,
	  FString::Printf(TEXT("Stamina: %.0f / %.0f"), Stamina, MaxStamina));
  }
}