// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "HealthComponent.h"

#include <Kismet/GameplayStatics.h>
#include "Engine/OverlapResult.h"

APlayerPawn::APlayerPawn()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	FireStartComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FireStartComponent"));
	FireStartComponent->SetupAttachment(BaseMeshComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) 
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer()) 
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)) 
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireCooldownTimer -= DeltaTime;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 12, FColor::Red);
		LookAt(HitResult.ImpactPoint);
	}

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPawn::MoveInput);
		EIC->BindAction(FireAction, ETriggerEvent::Triggered, this, &APlayerPawn::FireInput);
	}

}

void APlayerPawn::MoveInput(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);

	DeltaLocation.X = InputValue.X;
	DeltaLocation.Y = InputValue.Y;

	if (DeltaLocation.Length() > 1) {
		DeltaLocation.Normalize();
	}

	DeltaLocation = DeltaLocation * Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	AddActorWorldOffset(DeltaLocation, true);

}

void APlayerPawn::FireInput(const FInputActionValue& Value)
{
	bool InputValue = Value.Get<bool>();

	if (!InputValue || FireCooldownTimer > 0) {
		return;
	}

	FireCooldownTimer = FireRate;

	FVector Start = FireStartComponent->GetComponentLocation();
	FVector End = Start + FireStartComponent->GetForwardVector() * FireDistance;
	FVector StartToEnd = End - Start;
	FVector HalfwayPoint = Start + StartToEnd / 2;
	FQuat LineRotation = FireStartComponent->GetComponentQuat();
	FCollisionShape InteractionBox = FCollisionShape::MakeBox(FVector(FireDistance / 2, 25.0f, 25.0f));

	DrawDebugBox(GetWorld(), Start + StartToEnd / 2, FVector(FireDistance / 2, InteractionSphereRadius, InteractionSphereRadius), FQuat(StartToEnd.Rotation()), FColor::Blue, false, 1.0f);

	TArray<FOverlapResult> OverlapResult;
	bool HasOverlapped = GetWorld()->OverlapMultiByChannel(OverlapResult, HalfwayPoint, LineRotation, ECC_GameTraceChannel2, InteractionBox);

	if (!HasOverlapped) {
		return;
	}

	OverlapResult.Sort([&Start](const FOverlapResult& A, const FOverlapResult& B) {
			const AActor* ActorA = A.GetActor();
			const AActor* ActorB = B.GetActor();

			const float DistA = FVector::DistSquared(ActorA->GetActorLocation(), Start);
			const float DistB = FVector::DistSquared(ActorB->GetActorLocation(), Start);
			return DistA < DistB;
	});

	for (int i = 0; i <= Piercing && i < OverlapResult.Num(); i++) {
		AActor* OverlappedActor = OverlapResult[i].GetActor();
		if (UHealthComponent* HealthComponent = OverlappedActor->GetComponentByClass<UHealthComponent>()) {
			HealthComponent->Damage(Damage);
		}
	}

}

void APlayerPawn::HandleDestruction()
{
	UE_LOG(LogTemp, Display, TEXT("Player Died"));

	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), *CurrentLevelName);

}

void APlayerPawn::UpgradeDamage()
{
	Damage += 30;
}

void APlayerPawn::UpgradePiercing()
{
	Piercing += 1;
}

void APlayerPawn::UpgradeSpeed()
{
	Speed += 30;
}

void APlayerPawn::UpgradeFireRate()
{
	FireRate = FireRate * 0.9f;
}

void APlayerPawn::UpgradeRange()
{
	FireDistance += 25;
}
