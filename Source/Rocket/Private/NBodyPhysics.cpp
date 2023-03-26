// Fill out your copyright notice in the Description page of Project Settings.

#include "NBodyPhysics.h"
#include "CelestialBody.h"
#include "EngineUtils.h"
#include "Core/Tests/Containers/TestUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANBodyPhysics::ANBodyPhysics()
{
	PrimaryActorTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PrePhysics);
}

// Called when the game starts or when spawned
void ANBodyPhysics::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilation);

	for (TActorIterator<AActor> actor(GetWorld()); actor; ++actor)
	{
		TArray<UActorComponent*> Comps;
		actor->GetComponents(UGravityComponent::StaticClass(), Comps);
		if (Comps.Num())
		{
			this->GravityComponents.Add(Cast<UGravityComponent>(Comps[0]));
		}
	}
}

// Called every frame
void ANBodyPhysics::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Sum = FVector::Zero();

	for (const auto BodyA: GravityComponents)
	{
		if(!BodyA -> ReceivesGravity)
			continue;
		
		for (const auto BodyB: GravityComponents)
		{
			if(BodyA == BodyB || !BodyB -> CastsGravity)
				continue;

			FVector APos = BodyA->GetOwner()->GetActorLocation();
			FVector BPos = BodyB->GetOwner()->GetActorLocation();

			FVector AtoB = BPos - APos;
			double D = AtoB.Length();
			AtoB.Normalize();

			double Norm = BodyB->Mass;
			Norm /= D;
			if (InverseRoot)
			{
				Norm /= D;
			}
			
			BodyA -> AddAcceleration(Scaling * Norm * AtoB);
		}

		Sum += BodyA->GetAcceleration();
	}
}