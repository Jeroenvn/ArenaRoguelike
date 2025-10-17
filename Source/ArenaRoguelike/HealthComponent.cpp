// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "BasicEnemyPawn.h"
#include "PlayerPawn.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::Damage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0) {
		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetOwner())) {
			PlayerPawn->HandleDestruction();
		}
		if (ABasicEnemyPawn* EnemyPawn = Cast<ABasicEnemyPawn>(GetOwner())) {
			EnemyPawn->HandleDestruction();
		}
	}
}

void UHealthComponent::SetMaxHealth(float InMaxHealth, bool HealToFull)
{
	MaxHealth = InMaxHealth;
	
	if (HealToFull) {
		Health = MaxHealth;
	}
}

