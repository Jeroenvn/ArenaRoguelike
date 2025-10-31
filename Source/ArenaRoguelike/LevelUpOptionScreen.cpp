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
	OnOptionPicked.Broadcast(UpgradeOption0);
}

void ULevelUpOptionScreen::OnButton1Pressed()
{
	OnOptionPicked.Broadcast(UpgradeOption1);
}

void ULevelUpOptionScreen::OnButton2Pressed()
{
	OnOptionPicked.Broadcast(UpgradeOption2);
}

void ULevelUpOptionScreen::SetOptionMessage(int Index, FString Message, EUpgradeType upgrade)
{
	FText MessageText = FText::FromString(Message);
	switch (Index)
	{
	case 0:
		TextBlockOption0->SetText(MessageText);
		UpgradeOption0 = upgrade;
		break;
	case 1:
		TextBlockOption1->SetText(MessageText);
		UpgradeOption1 = upgrade;
		break;
	case 2:
		TextBlockOption2->SetText(MessageText);
		UpgradeOption2 = upgrade;
		break;
	default:
		break;
	}
}
