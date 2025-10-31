#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UpgradeType.h"

#include "LevelUpOptionScreen.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOptionPicked, EUpgradeType);

UCLASS()
class ARENAROGUELIKE_API ULevelUpOptionScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonOption0;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextBlockOption0;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonOption1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextBlockOption1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonOption2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextBlockOption2;

	void InitializeDelegates();

	UFUNCTION()
	void OnButton0Pressed();

	UFUNCTION()
	void OnButton1Pressed();

	UFUNCTION()
	void OnButton2Pressed();

	EUpgradeType UpgradeOption0;
	EUpgradeType UpgradeOption1;
	EUpgradeType UpgradeOption2;
	
	void SetOptionMessage(int Index, FString Message, EUpgradeType upgrade);

	FOnOptionPicked OnOptionPicked;
};
