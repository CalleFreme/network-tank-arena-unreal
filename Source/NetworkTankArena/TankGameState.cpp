// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameState.h"

#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

void ATankGameState::SetMatchPhaseFromServer(ETankMatchPhase NewPhase)
{
	if (!HasAuthority() || MatchPhase == ETankMatchPhase::Playing || MatchPhase == NewPhase)
	{
		return;
	}

	MatchPhase = NewPhase;
	OnRep_MatchPhase(); // RepNotify does not automatically run on the server
	ForceNetUpdate(); // immediately marks an actor to be considered for network replication on the CURRENT frame.
}

void ATankGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATankGameState, MatchPhase);
}

void ATankGameState::OnRep_MatchPhase()
{
	const FString Message = FString::Printf(TEXT("Match phase: %s"), LexToString(MatchPhase));
	UE_LOG(LogTemp, Display, TEXT("%s"), *Message);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	}
}