#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "LevelUpOptionScreen.generated.h"

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
	
	void SetOptionMessage(int Index, FString Message);
};
