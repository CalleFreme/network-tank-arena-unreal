#include "TankGameMode.h"

#include "TankPawn.h"
#include "TankGameState.h"
#include "TankPlayerState.h"
#include "TankDamageTestTarget.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"

ATankGameMode::ATankGameMode()
{
	// Reuse the established Blueprint visual composition and input asset assignments.
	static ConstructorHelpers::FClassFinder<ATankPawn> TankClass(TEXT("/Game/Blueprints/BP_Tank"));
	static ConstructorHelpers::FClassFinder<ATankPlayerController> ControllerClass(TEXT("/Game/Blueprints/BP_TankPlayerController"));
	DefaultPawnClass = TankClass.Succeeded() ? TankClass.Class.Get() : ATankPawn::StaticClass();
	PlayerControllerClass = ControllerClass.Succeeded() ? ControllerClass.Class.Get() : ATankPlayerController::StaticClass();

	GameStateClass = ATankGameState::StaticClass();
	PlayerStateClass = ATankPlayerState::StaticClass();
}

void ATankGameMode::StartPlay()
{
	// GameMode exists on the server. A placed target replaces this replicated fixture.
	if (HasAuthority() && GetNetMode() != NM_Client && !TActorIterator<ATankDamageTestTarget>(GetWorld()))
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		if (!GetWorld()->SpawnActor<ATankDamageTestTarget>(DamageTargetLocation, FRotator::ZeroRotator, Params))
		{
			UE_LOG(LogTemp, Warning, TEXT("Damage test target fixture could not spawn; check map clearance."));
		}
	}
	Super::StartPlay();
}

void ATankGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	EvaluateReadyGate();
}

void ATankGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	EvaluateReadyGate();
}

void ATankGameMode::HandlePlayerReadyChanged()
{
	EvaluateReadyGate();
}

void ATankGameMode::EvaluateReadyGate()
{
	ATankGameState* State = GetGameState<ATankGameState>();
	if (!State || State->GetMatchPhase() == ETankMatchPhase::Playing)
		return;

	int32 PlayerCount = 0;
	bool bAllReady = true;
	for (APlayerState* PlayerState : State->PlayerArray)
	{
		const ATankPlayerState* TankPlayerState = Cast<ATankPlayerState>(PlayerState);
		if (!TankPlayerState)
			continue;

		++PlayerCount;
		bAllReady &= TankPlayerState->IsReady();
	}

	ETankMatchPhase NextPhase;
	if (PlayerCount < 2)
	{
		NextPhase = ETankMatchPhase::WaitingForPlayers;
	}
	else if (bAllReady)
	{
		NextPhase = ETankMatchPhase::Playing;
	}
	else
	{
		NextPhase = ETankMatchPhase::WaitingForReady;
	}

	State->SetMatchPhaseFromServer(NextPhase);
}
