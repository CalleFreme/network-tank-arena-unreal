#pragma once

#include "CoreMinimal.h"
#include "TankMatchPhase.generated.h"

UENUM(BlueprintType)
enum class ETankMatchPhase : uint8
{
    WaitingForPlayers,
    WaitingForReady,
    Playing
};

inline const TCHAR* LexToString(ETankMatchPhase Phase)
{
    switch (Phase)
    {
    case ETankMatchPhase::WaitingForPlayers: return TEXT("WaitingForPlayers");
    case ETankMatchPhase::WaitingForReady: return TEXT("WaitingForReady");
    case ETankMatchPhase::Playing: return TEXT("Playing");
    default: return TEXT("Unknown");
    }
}