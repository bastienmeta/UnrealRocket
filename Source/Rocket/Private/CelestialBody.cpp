// Fill out your copyright notice in the Description page of Project Settings.


#include "CelestialBody.h"


// Sets default values
ACelestialBody::ACelestialBody()
{
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere"));
	UMaterial* Mat = LoadObject<UMaterial>(nullptr, TEXT("/Game/Mats/CelestialMat"));
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMeshComponent);

	// Mesh + Material
	StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->SetMaterial(0, Mat);

	// Physics
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->GetBodyInstance()->InertiaTensorScale = INFINITY * FVector::One();
	StaticMeshComponent->GetBodyInstance()->bUpdateMassWhenScaleChanges = false;
	StaticMeshComponent->SetLinearDamping(0.0);

	// Collisions
	StaticMeshComponent->SetGenerateOverlapEvents(true);
	SphereOverlap = CreateDefaultSubobject<USphereComponent>("Overlap Sphere");
	SphereOverlap->InitSphereRadius(50);	// 50 because a Sphere mesh is R50
	SphereOverlap->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SphereOverlap->SetGenerateOverlapEvents(true);
	SphereOverlap->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereOverlap->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	SphereOverlap->SetCollisionObjectType(ECC_GameTraceChannel1);
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &ACelestialBody::OnOverlapBegin);
	SphereOverlap->OnComponentEndOverlap.AddDynamic(this, &ACelestialBody::OnOverlapEnd);

	// Gravity
	GravityComponent = CreateDefaultSubobject<UGravityComponent>("Gravity Component");
	
	// Movement
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("Rotating Movement Component");
	RotatingMovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	RotatingMovementComponent->SetPlaneConstraintOrigin(FVector::ZeroVector);
}

void ACelestialBody::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	++CollisionCount;
}

void ACelestialBody::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	--CollisionCount;
}

// Called when the game starts or when spawned
void ACelestialBody::BeginPlay()
{
	Super::BeginPlay();

	// Apply changed values in editor

	// Mass
	StaticMeshComponent->SetMassOverrideInKg(NAME_None, GravityComponent->Mass);

	// Rotation speed
	// TODO abstract plane restriction to a component, using a plane in the scene
	RotatingMovementComponent->RotationRate = RotationSpeed * FRotator(0.0, 1.0, 0.0);

	// Restrict plane
	if (RestrictPlaneToXY)
	{
		RotatingMovementComponent->SetPlaneConstraintEnabled(true);
		RotatingMovementComponent->SnapUpdatedComponentToPlane();
	}

	// Receives gravity
	if(!GravityComponent -> ReceivesGravity)
	{
		StaticMeshComponent->SetSimulatePhysics(false);
	}
}

void ACelestialBody::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (RestrictPlaneToXY)
	{
		RotatingMovementComponent->SnapUpdatedComponentToPlane();
	}
}
