// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Mesh
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Meshes/4legs/4legs"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetStaticMesh(Mesh);

	// Physics
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->GetBodyInstance()->bUpdateMassWhenScaleChanges = false;
	StaticMeshComponent->SetLinearDamping(0.0);

	// Gravity
	GravityComponent = CreateDefaultSubobject<UGravityComponent>("Gravity Component");

	// Plane constraint
	MovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("Movement Component");
	MovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
	MovementComponent->SetPlaneConstraintOrigin(FVector::ZeroVector);
	MovementComponent->RotationRate = FRotator::ZeroRotator;

	// Rotational constraint
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("Physics constraints");
	PhysicsConstraint->ConstraintActor1 = this;
	PhysicsConstraint->ConstraintActor2 = nullptr;
	PhysicsConstraint->SetAngularSwing2Limit(ACM_Locked, 0);
	PhysicsConstraint->SetAngularTwistLimit(ACM_Locked, 0);
	PhysicsConstraint->SetLinearXLimit(LCM_Free, 0);
	PhysicsConstraint->SetLinearYLimit(LCM_Free, 0);
	PhysicsConstraint->SetLinearZLimit(LCM_Free, 0);
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->RotationRate = FRotator::ZeroRotator;

	if (RestrictPlaneToXY)
	{
		MovementComponent->SetPlaneConstraintEnabled(true);
		MovementComponent->SnapUpdatedComponentToPlane();
	}
	
	StaticMeshComponent->SetMassOverrideInKg(NAME_None, GravityComponent->Mass);

	if(!GravityComponent -> ReceivesGravity)
	{
		StaticMeshComponent->SetSimulatePhysics(false);
	}
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (RestrictPlaneToXY)
	{
		MovementComponent->SnapUpdatedComponentToPlane();
	}
}

void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// TODO use fucking enhanced input
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::Up, 1.f));
	PlayerInputComponent->BindAxis("MoveForward", this, &AShip::MoveForward);

	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Turn", EKeys::Left, -1.f));
	UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Turn", EKeys::Right, 1.f));
	PlayerInputComponent->BindAxis("Turn", this, &AShip::Turn);
}

void AShip::MoveForward(float Value)
{
	if(! Value)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("Forward %f"), Value);

	FVector Forward = GetActorForwardVector();
	StaticMeshComponent -> AddForce(Value * ThrustPower * Forward, NAME_None, true);
}

void AShip::Turn(float Value)
{
	if(! Value)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("Turning %f"), Value);

	StaticMeshComponent ->AddTorqueInRadians(Value * RotationPower * FVector::UpVector, NAME_None, true);
}