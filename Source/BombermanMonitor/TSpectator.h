// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "TSpectator.generated.h"

UCLASS()
class BOMBERMANMONITOR_API ATSpectator : public APawn
{
	GENERATED_BODY()

public:
	ATSpectator();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		USphereComponent *Collision;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UFloatingPawnMovement *Movement;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UCameraComponent *Camera;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
