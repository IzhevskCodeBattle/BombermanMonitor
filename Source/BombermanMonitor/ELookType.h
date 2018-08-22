#pragma once

UENUM(BlueprintType)
enum class ELookType : uint8
{
	LT_STATIC UMETA(DisplayName = "Static"),
	LT_MANUAL UMETA(DisplayName = "Manual"),
	LT_PLAYER UMETA(DisplayName = "Player")
};
