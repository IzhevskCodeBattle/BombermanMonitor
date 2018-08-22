// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDirector.generated.h"

UCLASS()
class BOMBERMANMONITOR_API ATDirector : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USceneComponent *Turret;
	ATDirector();
	void BeginPlay() override;
};
