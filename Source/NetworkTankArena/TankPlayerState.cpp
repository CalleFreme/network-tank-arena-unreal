// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerState.h"

#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

void ATankPlayerState::SetReadyFromServer(bool bNewReady)
{
	if (!HasAuthority() || bReady == bNewReady)
	{
		return;
	}
	bReady = bNewReady;
	OnRep_Ready(); // RepNotify does not automatically run on the server
	ForceNetUpdate(); // immediately marks an actor to be considered for network replication on the CURRENT frame.
}

void ATankPlayerState::OnRep_Ready()
{
	const FString Message = FString::Printf(TEXT("Player ready: %s"), bReady ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Display, TEXT("%s"), *Message);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	}
}

void ATankPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATankPlayerState, bReady);
}