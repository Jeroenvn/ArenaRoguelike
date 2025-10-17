// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpOptionScreen.h"

void ULevelUpOptionScreen::InitializeDelegates()
{
	ButtonOption0->OnClicked.AddDynamic(this, &ULevelUpOptionScreen::OnButton0Pressed);
	ButtonOption1->OnClicked.AddDynamic(this, &ULevelUpOptionScreen::OnButton1Pressed);
	ButtonOption2->OnClicked.AddDynamic(this, &ULevelUpOptionScreen::OnButton2Pressed);
}

void ULevelUpOptionScreen::OnButton0Pressed()
{
	OnOptionPicked.Broadcast(0);
}

void ULevelUpOptionScreen::OnButton1Pressed()
{
	OnOptionPicked.Broadcast(1);
}

void ULevelUpOptionScreen::OnButton2Pressed()
{
	OnOptionPicked.Broadcast(2);
}

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
