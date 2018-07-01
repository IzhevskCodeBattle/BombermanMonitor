// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TGround.h"
#include "TObject.h"
#include "TGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANMONITOR_API UTGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		int Size;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ATGround *Ground;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<ATObject*> Objects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category = "Classes")
		TSubclassOf<ATObject> Wall;

	UTGameInstance();

	UFUNCTION(BlueprintCallable)
		void Connect();

	UFUNCTION(BlueprintCallable)
		FString MakeConnectionString(FString _serverAddress, FString _serverPort, FString _userName, FString _code);

	UFUNCTION(BlueprintCallable)
		void ProcessAnswer(FString _answer);

	void CreateObject(int _x, int _y);
	void DestroyObject(int _x, int _y);
};
