// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPointsRow.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANMONITOR_API UTPointsRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FString Name;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int32 Points;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool ToDelete;
};
