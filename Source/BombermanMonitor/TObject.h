// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TObject.generated.h"

UCLASS()
class BOMBERMANMONITOR_API ATObject : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int X;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int Y;

	ATObject();
};
