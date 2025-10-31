#pragma once

#include "CoreMinimal.h"
#include "UpgradeType.generated.h"

UENUM(BlueprintType)
enum class EUpgradeType : uint8 {
	DAMAGE,
	FIRERATE,
	RANGE,
	PIERCE,
	SPEED
};