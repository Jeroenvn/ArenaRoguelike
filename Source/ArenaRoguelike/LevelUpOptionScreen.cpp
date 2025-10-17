// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpOptionScreen.h"

void ULevelUpOptionScreen::SetOptionMessage(int Index, FString Message)
{
	FText MessageText = FText::FromString(Message);
	switch (Index)
	{
	case 0:
		TextBlockOption0->SetText(MessageText);
		break;
	case 1:
		TextBlockOption1->SetText(MessageText);
		break;
	case 2:
		TextBlockOption2->SetText(MessageText);
		break;
	default:
		break;
	}
}
