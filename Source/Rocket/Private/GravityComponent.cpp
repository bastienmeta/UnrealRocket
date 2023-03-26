// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityComponent.h"

#include "Kismet/GameplayStatics.h"


UGravityComponent::UGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	SetTickGroup(ETickingGroup::TG_PrePhysics);
}

void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

	if(!Mesh)
	{
		UE_LOG(LogTemp, Error, TEXT("Gravity Component : cannot find Static Mesh on Actor"));
	}
}

void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ReceivesGravity)
	{
		Mesh->AddForce(Acceleration, NAME_None, true);
		Gravity = Acceleration;
		Acceleration = FVector::Zero();	
	}
}

void UGravityComponent::AddAcceleration(FVector A)
{
	this->Acceleration += A;
}

FVector UGravityComponent::GetAcceleration() const
{
	return this->Acceleration;
}
