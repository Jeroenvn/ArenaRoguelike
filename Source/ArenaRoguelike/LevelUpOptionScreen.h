#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "LevelUpOptionScreen.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOptionPicked, int);

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
	
	void SetOptionMessage(int Index, FString Message);

	FOnOptionPicked OnOptionPicked;
};
