// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GravityComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "CelestialBody.generated.h"

UCLASS()
class ROCKET_API ACelestialBody : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACelestialBody();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Body")
	bool RestrictPlaneToXY = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Celestial Body")
	int CollisionCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Body")
	float RotationSpeed = 0.0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Celestial Body")
	UGravityComponent* GravityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Body")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Body")
	USphereComponent* SphereOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Body")
	URotatingMovementComponent* RotatingMovementComponent;
};
