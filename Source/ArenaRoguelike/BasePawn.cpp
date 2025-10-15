// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	PivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PivotComponent"));
	PivotComponent->SetupAttachment(CapsuleComponent);

	BaseMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetupAttachment(PivotComponent);
}

void ABasePawn::LookAt(FVector Target)
{
	FVector VectorToTarget = Target - RootComponent->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, VectorToTarget.Rotation().Yaw, 0.0f);

	FRotator InterpolatedRotation = FMath::RInterpTo(PivotComponent->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);

	PivotComponent->SetWorldRotation(InterpolatedRotation);
}
