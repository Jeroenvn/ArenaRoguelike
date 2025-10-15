// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.h"
#include "BasicEnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class ARENAROGUELIKE_API ABasicEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	APlayerPawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	float Speed = 100;

	UPROPERTY(EditAnywhere)
	float Damage = 25;

	UPROPERTY(EditAnywhere)
	float DamageRate = 0.5f;

	UPROPERTY(VisibleAnywhere)
	float DamageCooldownTimer = 0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
