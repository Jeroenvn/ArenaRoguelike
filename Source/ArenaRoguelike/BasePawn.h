// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/CapsuleComponent.h"

#include "BasePawn.generated.h"

UCLASS()
class ARENAROGUELIKE_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* PivotComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BaseMeshComponent;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 10.0f;

	void LookAt(FVector Target);

};
