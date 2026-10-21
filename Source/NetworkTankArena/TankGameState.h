// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TankMatchPhase.h"
#include "TankGameState.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKTANKARENA_API ATankGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ETankMatchPhase GetMatchPhase() const { return MatchPhase; }
	
	void SetMatchPhaseFromServer(ETankMatchPhase NewPhase);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void OnRep_MatchPhase();

	UPROPERTY(ReplicatedUsing = OnRep_MatchPhase)
	ETankMatchPhase MatchPhase = ETankMatchPhase::WaitingForPlayers;
};
