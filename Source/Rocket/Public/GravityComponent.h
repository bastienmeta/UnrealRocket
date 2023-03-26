// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "GravityComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class ROCKET_API UGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGravityComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddAcceleration(FVector A);
	FVector GetAcceleration() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	double Mass = 1000.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	bool CastsGravity = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	bool ReceivesGravity = true;

	// Just indicative, correspond to the acceleration inflicted on the body at last frame
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gravity")
	FVector Gravity;

private:
	UStaticMeshComponent* Mesh;
	FVector Acceleration;
};
