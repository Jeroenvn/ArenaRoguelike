#include "ArenaRoguelikeGameMode.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "Kismet/GameplayStatics.h"

void AArenaRoguelikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		PlayerPawn = Cast<APlayerPawn>(Player);
	}

	APlayerController* FoundPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (FoundPlayerController) {
		PlayerController = FoundPlayerController;
		LevelUpOptionScreenWidget = CreateWidget<ULevelUpOptionScreen>(PlayerController, LevelUpOptionScreenClass);
		if (LevelUpOptionScreenWidget) {
			LevelUpOptionScreenWidget->AddToPlayerScreen();
			LevelUpOptionScreenWidget->SetVisibility(ESlateVisibility::Hidden);
			LevelUpOptionScreenWidget->InitializeDelegates();
			LevelUpOptionScreenWidget->OnOptionPicked.AddUObject(this, &AArenaRoguelikeGameMode::OnLevelUpOptionPicked);
		}
	}

	InitializePortals();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AArenaRoguelikeGameMode::SpawnEnemyAtRandomPortal, TimeBetweenSpawnLowerBoundary + (TimeBetweenSpawnBuffer * (1 / Difficulty)), true);

	FTimerHandle DifficultyTimerHandle;

	GetWorldTimerManager().SetTimer(DifficultyTimerHandle, this, &AArenaRoguelikeGameMode::IncreaseDifficultyPerSecond, 1.0f, true);

	ExperienceLeftBeforeLevelUp = ExperiencePerLevel;

	PlayerController->bShowMouseCursor = true;
}

void AArenaRoguelikeGameMode::InitializePortals()
{
	TArray<AActor*> PortalActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APortal::StaticClass(), PortalActors);

	for (AActor* PortalActor : PortalActors) {
		if (APortal* Portal = Cast<APortal>(PortalActor)) {
			Portals.Add(Portal);
		}
	}

	RandomizePortals();

}

void AArenaRoguelikeGameMode::RandomizePortals()
{
	RandomizedPortals = Portals;

	for (int32 i = RandomizedPortals.Num() - 1; i > 0; --i)
	{
		int32 j = FMath::RandRange(0, i);
		RandomizedPortals.Swap(i, j);
	}

}

void AArenaRoguelikeGameMode::SpawnEnemyAtRandomPortal()
{
	if (RandomizedPortals.IsEmpty()) {
		RandomizePortals();
	}

	APortal* Portal = RandomizedPortals.Pop();
	FVector SpawnLocation = Portal->GetSpawnPosition();
	FRotator SpawnRotation = Portal->GetSpawnRotation();
	SpawnEnemy(SpawnLocation, SpawnRotation);
}

void AArenaRoguelikeGameMode::SpawnEnemy(FVector location, FRotator rotation)
{
	ABasicEnemyPawn* Enemy = GetWorld()->SpawnActor<ABasicEnemyPawn>(BasicEnemyPawn, location, rotation);
	float Speed = enemyBaseSpeed + enemySpeedGrowth * Difficulty;
	float MaxHealth = enemyBaseHealth + enemyHealthGrowth * Difficulty;
	float Damage = enemyBaseDamage;
	Enemy->InitializeMonster(PlayerPawn, Speed, MaxHealth, Damage);
	Enemy->OnGiveExperience.AddUObject(this, &AArenaRoguelikeGameMode::AddExperience);
}

void AArenaRoguelikeGameMode::IncreaseDifficultyPerSecond()
{
	Difficulty += DifficultyIncreasePerMinute / 60;

	if (Difficulty - LastSpawnSpeedupDifficulty > 1.0f) {
		LastSpawnSpeedupDifficulty = Difficulty;
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AArenaRoguelikeGameMode::SpawnEnemyAtRandomPortal, TimeBetweenSpawnLowerBoundary + (TimeBetweenSpawnBuffer * (1 / Difficulty)), true);
	}
}

void AArenaRoguelikeGameMode::AddExperience(int ExperienceAmount)
{
	UE_LOG(LogTemp, Display, TEXT("Gained %d experience!"), ExperienceAmount);
	ExperienceLeftBeforeLevelUp -= ExperienceAmount;
	if (ExperienceLeftBeforeLevelUp <= 0) {
		LevelUp();
		ExperienceLeftBeforeLevelUp += ExperiencePerLevel;
	}
}

void AArenaRoguelikeGameMode::LevelUp()
{
	std::vector<EUpgradeType> allUpgradeTypes = {
		EUpgradeType::DAMAGE,
		EUpgradeType::FIRERATE,
		EUpgradeType::RANGE,
		EUpgradeType::PIERCE,
		EUpgradeType::SPEED
	};

	std::random_device randomDevice;
	std::mt19937 randomEngine(randomDevice());

	std::shuffle(allUpgradeTypes.begin(), allUpgradeTypes.end(), randomEngine);

	const int numUpgradesToSelect = 3;
	std::vector<EUpgradeType> chosenUpgrades(allUpgradeTypes.begin(), allUpgradeTypes.begin() + numUpgradesToSelect);

	int optionNumber = 0;

	for (const auto& upgrade : chosenUpgrades) {
		switch (upgrade) {
			case EUpgradeType::DAMAGE:
				LevelUpOptionScreenWidget->SetOptionMessage(optionNumber, "Damage", EUpgradeType::DAMAGE);
				break;
			case EUpgradeType::FIRERATE:
				LevelUpOptionScreenWidget->SetOptionMessage(optionNumber, "Fire rate", EUpgradeType::FIRERATE);
				break;
			case EUpgradeType::RANGE:
				LevelUpOptionScreenWidget->SetOptionMessage(optionNumber, "Range", EUpgradeType::RANGE);
				break;
			case EUpgradeType::PIERCE:
				LevelUpOptionScreenWidget->SetOptionMessage(optionNumber, "Pierce", EUpgradeType::PIERCE);
				break;
			case EUpgradeType::SPEED:
				LevelUpOptionScreenWidget->SetOptionMessage(optionNumber, "Speed", EUpgradeType::SPEED);
				break;
		}

		optionNumber++;
	}

	LevelUpOptionScreenWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AArenaRoguelikeGameMode::OnLevelUpOptionPicked(EUpgradeType upgrade)
{
	LevelUpOptionScreenWidget->SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UE_LOG(LogTemp, Display, TEXT("index picked: %d"), upgrade);

	switch (upgrade) {
	case EUpgradeType::DAMAGE:
		PlayerPawn->UpgradeDamage();
		break;
	case EUpgradeType::FIRERATE:
		PlayerPawn->UpgradeFireRate();
		break;
	case EUpgradeType::RANGE:
		PlayerPawn->UpgradeRange();
		break;
	case EUpgradeType::PIERCE:
		PlayerPawn->UpgradePiercing();
		break;
	case EUpgradeType::SPEED:
		PlayerPawn->UpgradeSpeed();
		break;
	}

}
