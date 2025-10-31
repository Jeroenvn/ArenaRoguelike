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

	DamageCooldownTimer = DamageCooldownSeconds;

	if (UHealthComponent* HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>()) {
		HealthComponent->Damage(Damage);
	}

}

void ABasicEnemyPawn::HandleDestruction()
{
	OnGiveExperience.Broadcast(10);
	UE_LOG(LogTemp, Display, TEXT("Enemy Died"));
	Destroy();

}

void ABasicEnemyPawn::InitializeMonster(APlayerPawn* InPlayerPawn, float InSpeed, int InMaxHealth, float InDamage)
{
	PlayerPawn = InPlayerPawn;
	Speed = InSpeed;
	GetComponentByClass<UHealthComponent>()->SetMaxHealth(InMaxHealth, true);
	Damage = InDamage;
}
