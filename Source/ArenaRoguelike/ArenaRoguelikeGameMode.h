// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PlayerPawn.h"
#include "BasicEnemyPawn.h"
#include "Portal.h"

#include "ArenaRoguelikeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ARENAROGUELIKE_API AArenaRoguelikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	APlayerPawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasicEnemyPawn> BasicEnemyPawn;

	TArray<APortal*> Portals;

	TArray<APortal*> RandomizedPortals;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere)
	float TimeBetweenSpawns = 2.5f;

	void InitializePortals();

	void RandomizePortals();

	void SpawnEnemyAtRandomPortal();

	void SpawnEnemy(FVector location);

};
