// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TObject.h"
#include "TPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANMONITOR_API ATPlayer : public ATObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FString Name;

	ATPlayer();
};
