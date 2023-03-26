// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GravityComponent.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "ShipInputsDataAsset.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "Ship.generated.h"

UCLASS()
class ROCKET_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void Turn(float Value);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ship")
	UGravityComponent* GravityComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ship")
	URotatingMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ship")
	UPhysicsConstraintComponent* PhysicsConstraint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	bool RestrictPlaneToXY = true;
	
	// in m.s-2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship")
	float ThrustPower = 10000;

	// in rad.s-2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ship")
	float RotationPower = 10;
};
