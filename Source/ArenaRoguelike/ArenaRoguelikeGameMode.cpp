// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaRoguelikeGameMode.h"

#include "Kismet/GameplayStatics.h"

void AArenaRoguelikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		PlayerPawn = Cast<APlayerPawn>(Player);
	}

	InitializePortals();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AArenaRoguelikeGameMode::SpawnEnemyAtRandomPortal, TimeBetweenSpawns, true);

	FTimerHandle DifficultyTimerHandle;

	GetWorldTimerManager().SetTimer(DifficultyTimerHandle, this, &AArenaRoguelikeGameMode::IncreaseDifficultyPerSecond, 1.0f, true);

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
	SpawnEnemy(SpawnLocation);
}

void AArenaRoguelikeGameMode::SpawnEnemy(FVector location)
{
	ABasicEnemyPawn* Enemy = GetWorld()->SpawnActor<ABasicEnemyPawn>(BasicEnemyPawn, location, FRotator(0.0f, 0.0f, 0.0f));
	float Speed = 100 * Difficulty;
	float MaxHealth = 100 * Difficulty;
	float Damage = 25;
	Enemy->InitializeMonster(PlayerPawn, Speed, MaxHealth, Damage);
}

void AArenaRoguelikeGameMode::IncreaseDifficultyPerSecond()
{
	Difficulty += DifficultyIncreasePerMinute / 60;
}
