// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyPawn.h"
#include "HealthComponent.h"

void ABasicEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentHit.AddDynamic(this, &ABasicEnemyPawn::OnHit);

}

void ABasicEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DamageCooldownTimer -= DeltaTime;

	if (PlayerPawn) {
		LookAt(PlayerPawn->GetActorLocation());
		FVector DeltaLocation = PivotComponent->GetForwardVector();
		DeltaLocation = DeltaLocation * DeltaTime * Speed;
		AddActorWorldOffset(DeltaLocation, true);
	}
}

void ABasicEnemyPawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (DamageCooldownTimer > 0) {
		return;
	}

	DamageCooldownTimer = DamageRate;

	if (UHealthComponent* HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>()) {
		HealthComponent->Damage(Damage);
		UE_LOG(LogTemp, Display, TEXT("Actor damaged: %s"), *OtherActor->GetActorNameOrLabel());
	}
}
