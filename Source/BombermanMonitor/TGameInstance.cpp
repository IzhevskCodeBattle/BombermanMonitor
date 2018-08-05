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

		for (auto player : Players)
		{
			player->ToDelete = true;
		}
		for (auto player : JsonObject->GetArrayField("playerInfoList"))
		{
			FString name = player->AsObject()->GetStringField("name");
			int score = player->AsObject()->GetIntegerField("score");
			UpdatePlayer(name, player->AsObject()->GetIntegerField("x"), player->AsObject()->GetIntegerField("y"));
		};
		Players.RemoveAll([](ATPlayer *_object)
		{
			if (_object->ToDelete)
			{
				_object->Destroy();
				return true;
			}
			return false;
		});

		int i = 0;
		for (auto chopper : JsonObject->GetArrayField("choppers"))
		{
			i++;
			UpdateChopper(i, chopper->AsObject()->GetIntegerField("x"), chopper->AsObject()->GetIntegerField("y"));
		};

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
					CreateSolidWall(i, j);
					break;

				case L'#':
					CreateWall(i, j);
					break;

				case L'1': CreateBomb(i, j, 1); break;
				case L'2': CreateBomb(i, j, 2); break;
				case L'3': CreateBomb(i, j, 3); break;
				case L'4': CreateBomb(i, j, 4); break;
				case L'5': CreateBomb(i, j, 5); break;

				default:
					break;
				}
				position++;
			}
		}
	}
}

template<typename T> T* UTGameInstance::CreateObject(int _x, int _y, TSubclassOf<T> &_type)
{
	T *result = nullptr;

	if (Objects.Num() > 0)
	{
		ATObject **resultPtr = Objects.FindByPredicate([&](const ATObject *t) { return t->X == _x && t->Y == _y; });
		if (resultPtr)
		{
			result = (T*)(*resultPtr);
		}
	}

	if (result == nullptr)
	{
		FVector initialLocation(_x * 100 + 50, _y * 100 + 50, 50);

		result = GetWorld()->SpawnActor<T>(_type, initialLocation, FRotator::ZeroRotator);
		result->X = _x;
		result->Y = _y;
		Objects.Add(result);
	}

	return result;
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

void UTGameInstance::CreateSolidWall(int _x, int _y)
{
	CreateObject<ATObject>(_x, _y, SolidWall);
}

void UTGameInstance::CreateWall(int _x, int _y)
{
	CreateObject<ATObject>(_x, _y, Wall);
}

void UTGameInstance::CreateBomb(int _x, int _y, int _counter)
{
	CreateObject<ATCounterObject>(_x, _y, Bomb)->Counter = _counter;
}

void UTGameInstance::CreateBoom(int _x, int _y)
{
	CreateObject<ATObject>(_x, _y, Boom);
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

void UTGameInstance::UpdatePlayer(FString &_name, int _x, int _y)
{
	ATPlayer *result = nullptr;

	if (Players.Num() > 0)
	{
		ATPlayer **resultPtr = Players.FindByPredicate([&](const ATPlayer *p) { return p->Name == _name; });
		if (resultPtr)
		{
			result = *resultPtr;
		}
	}

	if (result == nullptr)
	{
		FVector initialLocation(_x * 100 + 50, _y * 100 + 50, 50);

		result = GetWorld()->SpawnActor<ATPlayer>(Player, initialLocation, FRotator::ZeroRotator);
		result->Name = _name;
		result->X = _x;
		result->Y = _y;
		Objects.Add(result);
	}

	result->ToX = _x;
	result->ToY = _y;

	result->ToDelete = false;
}

void UTGameInstance::UpdateChopper(int _i, int _x, int _y)
{
	ATMovableObject *result = nullptr;

	if (Choppers.Num() > _i)
	{
		result = Choppers[_i];
	}
	else
	{
		FVector initialLocation(_x * 100 + 50, _y * 100 + 50, 50);

		result = GetWorld()->SpawnActor<ATMovableObject>(Chopper, initialLocation, FRotator::ZeroRotator);
		result->X = _x;
		result->Y = _y;
		Choppers.EmplaceAt(_i, result);
	}

	result->ToX = _x;
	result->ToY = _y;
}
