// Fill out your copyright notice in the Description page of Project Settings.

#include "TPointsTable.h"
#include "TPointsRow.h"
#include "TGameInstance.h"

void UTPointsTable::StartUpdate()
{
	if (List)
	{
		int32 rowCount = List->GetChildrenCount();
		for (int32 i = 0; i < rowCount; i++)
		{
			Cast<UTPointsRow>(List->GetChildAt(i))->ToDelete = true;
		}
	}
}

void UTPointsTable::UpdatePlayerPoints(const FString &_name, int32 _points)
{
	if (List)
	{
		UTPointsRow *row;
		int32 rowCount = List->GetChildrenCount();
		for (int32 i = 0; i < rowCount; i++)
		{
			row = Cast<UTPointsRow>(List->GetChildAt(i));
			if (row && row->Name == _name)
			{
				row->Points = _points;
				row->ToDelete = false;
				return;
			}
		}
		row = CreateWidget<UTPointsRow>(gameInstance, gameInstance->PointsRow);
		row->Name = _name;
		row->Points = _points;
		row->ToDelete = false;
		List->AddChild(row);
	}
}

void UTPointsTable::EndUpdate()
{
	if (List)
	{
		int32 rowCount = List->GetChildrenCount();
		for (int32 i = 0; i < rowCount; i++)
		{
			UTPointsRow *row = Cast<UTPointsRow>(List->GetChildAt(i));
			if (row && row->ToDelete == true)
			{
				row->RemoveFromParent();
			}
		}
	}
}
