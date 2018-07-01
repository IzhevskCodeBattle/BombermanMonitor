// Fill out your copyright notice in the Description page of Project Settings.

#include "TGameInstance.h"
#include "Engine.h"
//#include "ThirdParty\libWebSockets\libwebsockets\include\Win64\2015\libwebsockets.h"

UTGameInstance::UTGameInstance()
{
}

void UTGameInstance::Connect()
{
	
}

FString UTGameInstance::MakeConnectionString(FString _serverAddress, FString _serverPort, FString _userName, FString _code)
{
	return "ws://" + _serverAddress + ":" + _serverPort + "/codenjoy-contest/ws?user=" + _userName + "&code=" + _code;
}

void UTGameInstance::ProcessAnswer(FString _answer)
{
	if (_answer.StartsWith("board="))
	{
		_answer = _answer.RightChop(6);

		int size = FMath::Sqrt(_answer.Len());
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
				switch (_answer[position])
				{
				case L' ':
					DestroyObject(i, j);
					break;

				default:
					CreateObject(i, j);
					break;
				}
				position++;
			}
		}
		_answer.RightChop(position);
	}
	else
	{
		_answer = _answer.RightChop(6);
	}
}

void UTGameInstance::CreateObject(int _x, int _y)
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

		result = GetWorld()->SpawnActor<ATObject>(Wall, initialLocation, FRotator::ZeroRotator);

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
