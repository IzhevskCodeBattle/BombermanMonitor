// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TObject.h"
#include "TMovableObject.generated.h"

UCLASS()
class BOMBERMANMONITOR_API ATMovableObject : public ATObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int ToX;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int ToY;

	ATMovableObject();
	void Tick(float DeltaTime) override;
};
