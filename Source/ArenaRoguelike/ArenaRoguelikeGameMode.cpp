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

	for (int i = 0; i < 4; i++) {
		if (RandomizedPortals.IsEmpty()) {
			RandomizePortals();
		}

		APortal* Portal = RandomizedPortals.Pop();
		FVector SpawnLocation = Portal->GetSpawnPosition();
		SpawnEnemy(SpawnLocation);
	}

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
	UE_LOG(LogTemp, Display, TEXT("Randomizing Portals"));

	for (int32 i = RandomizedPortals.Num() - 1; i > 0; --i)
	{
		int32 j = FMath::RandRange(0, i);
		RandomizedPortals.Swap(i, j);
	}

}

void AArenaRoguelikeGameMode::SpawnEnemy(FVector location)
{
	ABasicEnemyPawn* Enemy = GetWorld()->SpawnActor<ABasicEnemyPawn>(BasicEnemyPawn, location, FRotator(0.0f, 0.0f, 0.0f));
	Enemy->PlayerPawn = PlayerPawn;
}
