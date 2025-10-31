#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PlayerPawn.h"
#include "BasicEnemyPawn.h"
#include "Portal.h"
#include "LevelUpOptionScreen.h"
#include "UpgradeType.h"

#include "ArenaRoguelikeGameMode.generated.h"

UCLASS()
class ARENAROGUELIKE_API AArenaRoguelikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	APlayerPawn* PlayerPawn;

	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULevelUpOptionScreen> LevelUpOptionScreenClass;

	ULevelUpOptionScreen* LevelUpOptionScreenWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasicEnemyPawn> BasicEnemyPawn;

	TArray<APortal*> Portals;

	TArray<APortal*> RandomizedPortals;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category="Enemy")
	float enemyBaseSpeed = 130;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float enemySpeedGrowth = 20;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float enemyBaseHealth = 40;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float enemyHealthGrowth = 50;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float enemyBaseDamage = 25;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float TimeBetweenSpawnBuffer = 1.5f;

	float TimeBetweenSpawnLowerBoundary = 0.3f;

	float LastSpawnSpeedupDifficulty = 1.0f;

	float DifficultyIncreasePerMinute = 1.0f;


	UPROPERTY(VisibleAnywhere, Category = "Difficulty")
	float Difficulty = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Leveling")
	int ExperiencePerLevel = 30;

	UPROPERTY(VisibleAnywhere, Category = "Leveling")
	int ExperienceLeftBeforeLevelUp;

	void InitializePortals();

	void RandomizePortals();

	void SpawnEnemyAtRandomPortal();

	void SpawnEnemy(FVector location, FRotator rotation);

	void IncreaseDifficultyPerSecond();

	void AddExperience(int ExperienceAmount);

	void LevelUp();

	void OnLevelUpOptionPicked(EUpgradeType upgrade);

};
