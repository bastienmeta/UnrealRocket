// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GravityComponent.h"
#include "GameFramework/Actor.h"
#include "NBodyPhysics.generated.h"

UCLASS()
class ROCKET_API ANBodyPhysics : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ANBodyPhysics();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gravity")
	TArray<UGravityComponent*> GravityComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gravity")
	double Scaling = 1000.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gravity")
	bool InverseRoot = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gravity")
	float TimeDilation = 1.0;
};