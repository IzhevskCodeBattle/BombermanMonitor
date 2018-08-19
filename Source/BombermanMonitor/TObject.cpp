// Fill out your copyright notice in the Description page of Project Settings.

#include "TObject.h"

ATObject::ATObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATObject::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	FVector target(X * 100 + 50, Y * 100 + 50, 0);

	FVector pos = GetActorLocation();

	float speed = 100 * _deltaTime;
	float distSquared = FVector::DistSquared(pos, target);
	if (distSquared > 0)
	{
		if (distSquared < 1)
		{
			pos = target;
		}
		else
		{
			FVector dir = (target - pos).GetSafeNormal();
			FRotator rot = FMatrix(dir, FVector(-dir.Y, dir.X, dir.Z), FVector::UpVector, FVector::ZeroVector).Rotator();
			SetRotation(rot);

			if (distSquared <= 10000)
			{
				pos += dir * _deltaTime * 100;
			}
			else
			{
				pos += dir * _deltaTime * 200;
			}
		}
		SetActorLocation(pos);
	}
}

void ATObject::Dead()
{
	if (IsDead == false)
	{
		IsDead = true;
		SetActorLocation(FVector(X * 100 + 50, Y * 100 + 50, 0));
		Dead_BP();
	}
}

void ATObject::Renew()
{
	if (IsDead)
	{
		IsDead = false;
		SetActorLocation(FVector(X * 100 + 50, Y * 100 + 50, 0));
		Renew_BP();
	}
}
