// Fill out your copyright notice in the Description page of Project Settings.

#include "TGameInstance.h"
#include "Engine.h"

void UTGameInstance::OnResponseReceived(FHttpRequestPtr _request, FHttpResponsePtr _response, bool _wasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		FString map = JsonObject->GetStringField("map");

		//////////////////////////////////////////////
		FString map2;
		for (int i = 0; i < map.Len(); i++)
		{
			if (map[i] != '\n')
				map2.AppendChar(map[i]);
		}
		map = map2;
		//////////////////////////////////////////////
		int size = FMath::Sqrt(map.Len());
		if (Ground && size != Size)
		{
			Ground->Init(size);
		}
		Size = size;

		int position = 0;
		for (int j = 0; j < Size; j++)
		{
			for (int i = 0; i < Size; i++)
			{
				switch (map[position])
				{
				case L' ':
					DestroyObject(i, j);
					break;

				case L'☼':
					CreateObject(i, j, 1);
					break;

				case L'#':
					CreateObject(i, j, 2);
					break;

				default:
					CreateObject(i, j, 0);
					break;
				}
				position++;
			}
		}
	}
}

UTGameInstance::UTGameInstance()
{
}

void UTGameInstance::Connect(FString _serverAddress, FString _serverPort)
{
	http = &FHttpModule::Get();
	url = "http://" + _serverAddress + ":" + _serverPort + "/codenjoy-contest/rest/game/bomberman";
}

void UTGameInstance::Update()
{
	TSharedRef<IHttpRequest> Request = http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UTGameInstance::OnResponseReceived);
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UTGameInstance::CreateObject(int _x, int _y, int _type)
{
	ATObject *result = nullptr;

	if (Objects.Num() > 0)
	{
		ATObject **resultPtr = Objects.FindByPredicate([&](const ATObject *t) { return t->X == _x && t->Y == _y; });
		if (resultPtr)
		{
			result = *resultPtr;
		}
	}

	if (result == nullptr)
	{
		FVector initialLocation(_x * 100 + 50, _y * 100 + 50, 50);

		switch (_type)
		{
		case 1:
			result = GetWorld()->SpawnActor<ATObject>(SolidWall, initialLocation, FRotator::ZeroRotator);
			break;

		case 2:
			result = GetWorld()->SpawnActor<ATObject>(Wall, initialLocation, FRotator::ZeroRotator);
			break;

		default:
			result = GetWorld()->SpawnActor<ATObject>(Object, initialLocation, FRotator::ZeroRotator);
			break;
		}

		result->X = _x;
		result->Y = _y;
		Objects.Add(result);
	}
}

void UTGameInstance::DestroyObject(int _x, int _y)
{
	if (Objects.Num() > 0)
	{
		ATObject **resultPtr = Objects.FindByPredicate([&](const ATObject *t) { return t->X == _x && t->Y == _y; });
		if (resultPtr)
		{
			(*resultPtr)->Destroy();
		}
	}
}
