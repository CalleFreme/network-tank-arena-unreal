// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NETWORKTANKARENA_API ATankPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	bool IsReady() const { return bReady; }
	void SetReadyFromServer(bool bNewReady);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void OnRep_Ready();

	UPROPERTY(ReplicatedUsing = OnRep_Ready)
	bool bReady = false;
};
