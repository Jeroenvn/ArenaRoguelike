// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	PivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PivotComponent"));
	SetRootComponent(PivotComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(PivotComponent);

	SpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnComponent"));
	SpawnComponent->SetupAttachment(PivotComponent);

}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector APortal::GetSpawnPosition()
{
	return FVector(SpawnComponent->GetComponentLocation());

}

FRotator APortal::GetSpawnRotation()
{
	return FRotator(SpawnComponent->GetComponentRotation());
}

