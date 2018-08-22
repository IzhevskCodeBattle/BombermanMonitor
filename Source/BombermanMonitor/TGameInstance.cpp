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

		int size = FMath::Sqrt(map.Len());
		if (size != Size)
		{
			if (Ground)
				Ground->Init(size);
			Size = size;
		}

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
				case L'H':
					DestroyWall(i, j);
					break;

				case L'҉':
					CreateBoom(i, j);
					break;

				case L'1': CreateBomb(i, j, 1); break;
				case L'2': CreateBomb(i, j, 2); break;
				case L'3': CreateBomb(i, j, 3); break;
				case L'4': CreateBomb(i, j, 4); break;
				case L'5': CreateBomb(i, j, 5); break;
				}
				position++;
			}
		}

		for (auto player : JsonObject->GetArrayField("playerInfoList"))
		{
			FString name = player->AsObject()->GetStringField("name");
			int score = player->AsObject()->GetIntegerField("score");
			int x = player->AsObject()->GetIntegerField("x");
			int y = player->AsObject()->GetIntegerField("y");
			//////////////////////
			y = Size - y - 1;
			//////////////////////
			TCHAR state = map[y*Size + x];
			UpdatePlayer(name, x, y, state);
		};

		int i = 0;
		for (auto chopper : JsonObject->GetArrayField("choppers"))
		{
			i++;
			int x = chopper->AsObject()->GetIntegerField("x");
			int y = chopper->AsObject()->GetIntegerField("y");
			//////////////////////
			y = Size - y - 1;
			//////////////////////
			TCHAR state = map[y*Size + x];
			UpdateChopper(i, x, y, state);
		};
	}
}

template<typename T> T* UTGameInstance::CreateObject(int _x, int _y, TSubclassOf<T> &_type)
{
	ATObject *result;
	ATObject **resultPtr = Objects.FindByPredicate([_x, _y](ATObject *obj) {return obj->X == _x && obj->Y == _y; });
	if (resultPtr)
	{
		result = *resultPtr;
	}
	else
	{
		result = GetWorld()->SpawnActor<T>(_type, GetVectorByCoords(_x, _y), FRotator::ZeroRotator);
		Objects.Add(result);
	}

	result->X = _x;
	result->Y = _y;

	return (T*)result;
}

UTGameInstance::UTGameInstance()
{
}

void UTGameInstance::Connect(FString _serverAddress, FString _serverPort)
{
	http = &FHttpModule::Get();
	url = "http://" + _serverAddress + ":" + _serverPort + "/codenjoy-contest/rest/game/bomberman";
}

void UTGameInstance::Disconnect()
{
	Size = 0;
	Ground->Init(0);
	Objects.RemoveAll([](ATObject *obj) {obj->Destroy(); return true; });
	Players.RemoveAll([](ATPlayer *obj) {obj->Destroy(); return true; });
	Choppers.RemoveAll([](ATObject *obj) {obj->Destroy(); return true; });
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

void UTGameInstance::DestroyWall(int _x, int _y)
{
	CreateObject<ATObject>(_x, _y, Wall)->Dead();
}

void UTGameInstance::CreateBomb(int _x, int _y, int _counter)
{
	CreateObject<ATCounterObject>(_x, _y, Bomb)->Counter = _counter;
}

void UTGameInstance::CreateBoom(int _x, int _y)
{
	CreateObject<ATObject>(_x, _y, Boom)->Dead();
}

void UTGameInstance::DestroyObject(int _x, int _y)
{
	Objects.RemoveAll([_x, _y](ATObject *obj)
	{
		if (obj->X == _x && obj->Y == _y)
		{
			obj->Destroy();
			return true;
		}
		return false;
	});
}

void UTGameInstance::UpdatePlayer(FString &_name, int _x, int _y, TCHAR _state)
{
	ATPlayer *result;
	ATPlayer **resultPtr = Players.FindByPredicate([_name](ATPlayer *obj) {return obj->Name == _name; });
	if (resultPtr)
	{
		result = *resultPtr;
	}
	else
	{
		result = GetWorld()->SpawnActor<ATPlayer>(Player, GetVectorByCoords(_x, _y), FRotator::ZeroRotator);
		result->Name = _name;
		Players.Add(result);
	}

	result->X = _x;
	result->Y = _y;
	if (_state == L'Ѡ' || _state == L'♣')
		result->Dead();
	else
		result->Renew();
}

void UTGameInstance::UpdateChopper(int _i, int _x, int _y, TCHAR _state)
{
	ATObject *result;
	if (Choppers.Num() > _i)
	{
		result = Choppers[_i];
	}
	else
	{
		result = GetWorld()->SpawnActor<ATObject>(Chopper, GetVectorByCoords(_x, _y), FRotator::ZeroRotator);
		Choppers.Add(result);
	}

	result->X = _x;
	result->Y = _y;
	if (_state == L'x')
		result->Dead();
	else
		result->Renew();
}
