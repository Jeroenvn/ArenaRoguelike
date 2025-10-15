// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyPawn.h"

void ABasicEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn) {
		LookAt(PlayerPawn->GetActorLocation());
		FVector DeltaLocation = PivotComponent->GetForwardVector();
		DeltaLocation = DeltaLocation * DeltaTime * Speed;
		AddActorWorldOffset(DeltaLocation);
	}
}
