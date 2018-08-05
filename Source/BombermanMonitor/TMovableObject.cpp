// Fill out your copyright notice in the Description page of Project Settings.

#include "TMovableObject.h"

ATMovableObject::ATMovableObject()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATMovableObject::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	FVector target(ToX * 100, ToY * 100, 0);

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
			//SetRotation(rot);

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
