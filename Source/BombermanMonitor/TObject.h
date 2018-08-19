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
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool IsDead;

	ATObject();
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void SetRotation(const FRotator &_rotation);

	UFUNCTION(BlueprintCallable)
		void Dead();
	UFUNCTION(BlueprintImplementableEvent)
		void Dead_BP();
	UFUNCTION(BlueprintCallable)
		void Renew();
	UFUNCTION(BlueprintImplementableEvent)
		void Renew_BP();
};
