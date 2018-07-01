// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TGround.generated.h"

UCLASS()
class BOMBERMANMONITOR_API ATGround : public AActor
{
	GENERATED_BODY()

public:
	ATGround();

	UFUNCTION(BlueprintImplementableEvent)
		void Init(int _size);
};
