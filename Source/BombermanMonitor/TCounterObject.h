// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TObject.h"
#include "TCounterObject.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANMONITOR_API ATCounterObject : public ATObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int Counter;
};
