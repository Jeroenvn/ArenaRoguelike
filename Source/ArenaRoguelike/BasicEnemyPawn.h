#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.h"
#include "BasicEnemyPawn.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGiveExperience, int);

UCLASS()
class ARENAROGUELIKE_API ABasicEnemyPawn : public ABasePawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	APlayerPawn* PlayerPawn;

	float Speed;
	float Damage;
	float DamageCooldownSeconds = 0.5f;
	float DamageCooldownTimer = 0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void HandleDestruction();

	void InitializeMonster(APlayerPawn* InPlayerPawn, float InSpeed, int InMaxHealth, float InDamage);

	FOnGiveExperience OnGiveExperience;

};
