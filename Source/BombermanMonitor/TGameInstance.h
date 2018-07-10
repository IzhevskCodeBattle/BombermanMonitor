// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Online/HTTP/Public/Http.h"
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

private:
	FHttpModule * http;
	FString url;

	void OnResponseReceived(FHttpRequestPtr _request, FHttpResponsePtr _response, bool _wasSuccessful);

public:

	UPROPERTY(BlueprintReadOnly)
		int Size;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ATGround *Ground;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<ATObject*> Objects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATObject> Object;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATObject> SolidWall;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes")
		TSubclassOf<ATObject> Wall;

	UTGameInstance();

	UFUNCTION(BlueprintCallable)
		void Connect(FString _serverAddress, FString _serverPort);

	UFUNCTION(BlueprintCallable)
		void Update();

	void CreateObject(int _x, int _y, int _type);
	void DestroyObject(int _x, int _y);
};
