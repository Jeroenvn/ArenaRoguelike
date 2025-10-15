// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaRoguelikeGameMode.h"

#include "Kismet/GameplayStatics.h"

void AArenaRoguelikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) {
		PlayerPawn = Cast<APlayerPawn>(Player);
	}

	SpawnEnemy(FVector(300.0f, 300.0f, 60.0f));

	TArray<AActor*> Portals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APortal::StaticClass(), Portals);

	for (AActor* PortalActor : Portals) {
		if (APortal* Portal = Cast<APortal>(PortalActor)) {
			FVector pos = Portal->GetSpawnPosition();
			SpawnEnemy(pos);
		}
	}

}

void AArenaRoguelikeGameMode::SpawnEnemy(FVector location)
{
	ABasicEnemyPawn* Enemy = GetWorld()->SpawnActor<ABasicEnemyPawn>(BasicEnemyPawn, location, FRotator(0.0f, 0.0f, 0.0f));
	Enemy->PlayerPawn = PlayerPawn;
}
