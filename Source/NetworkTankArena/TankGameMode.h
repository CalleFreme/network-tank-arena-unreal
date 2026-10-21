#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"

// Standard GameMode login/restart creates and possesses one tank per connection.
UCLASS()
class NETWORKTANKARENA_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATankGameMode();
	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	void HandlePlayerReadyChanged();

private:
	void EvaluateReadyGate();

	UPROPERTY(EditDefaultsOnly, Category = "Tank|Combat Test")
	FVector DamageTargetLocation = FVector(0.0, 500.0, 100.0);
};
