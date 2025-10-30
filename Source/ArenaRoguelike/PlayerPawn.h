// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

#include "PlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class ARENAROGUELIKE_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* FireStartComponent;

	UPROPERTY(EditAnywhere)
	float Speed = 300;

	UPROPERTY(EditAnywhere)
	float FireDistance = 200;

	UPROPERTY(EditAnywhere)
	float InteractionSphereRadius = 20;

	UPROPERTY(EditAnywhere)
	int Piercing = 1;

	UPROPERTY(EditAnywhere)
	float Damage = 50;

	UPROPERTY(EditAnywhere)
	float FireRate = 1;

	UPROPERTY(VisibleAnywhere)
	float FireCooldownTimer = 0;

	void MoveInput(const FInputActionValue& Value);

	void FireInput(const FInputActionValue& Value);

	void HandleDestruction();

	void UpgradeDamage();
	void UpgradePiercing();
	void UpgradeSpeed();
	void UpgradeFireRate();
	void UpgradeRange();

};
