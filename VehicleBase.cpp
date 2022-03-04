// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#define BINDAXIS(AxisName,Class,Method) PlayerInputComponent->BindAxis(TEXT( #AxisName ), this, & ## Class ## :: ## Method );



// Sets default values
AVehicleBase::AVehicleBase():Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BaseLookUpRate = 45.0f;
	BaseLookRightRate = 45.0f;

	CurrentDeltaRotation = FRotator(45.0f, 45.0f, 0.0f);

	bInversePitch = false;

	CharacterMovementComponent = CastChecked<UCharacterMovementComponent>(GetMovementComponent());

	//CharacterMovementComponent->SetMovementMode(MOVE_Flying);

	DeltaRotation = FRotator(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Brake"),EInputEvent::IE_Pressed ,this, &AVehicleBase::BrakePress);

	BINDAXIS(LookUp, AVehicleBase, ControllerLookup);
	BINDAXIS(LookRight, AVehicleBase, ControllerLookRight);
	BINDAXIS(TurnUp, AVehicleBase, TurnUp);
	BINDAXIS(TurnRight, AVehicleBase, TurnRight);
	BINDAXIS(MoveForward, AVehicleBase, MoveForward);
}

void AVehicleBase::BrakePress()
{
	// to do .respond to movement mode
	CharacterMovementComponent->BrakingDecelerationFlying += Deceleration;
}

void AVehicleBase::BrakeUnpress()
{
	CharacterMovementComponent->BrakingDecelerationFlying -= Deceleration;
}

void AVehicleBase::ControllerLookup(float InScale)
{
	AddControllerPitchInput(InScale * BaseLookUpRate);
}

void AVehicleBase::ControllerLookRight(float InScale)
{

	AddControllerYawInput(InScale * BaseLookRightRate);

}

void AVehicleBase::TurnUp(float InScale)
{
	float factor = bInversePitch ? -1.0f : 1.0f;
	float TargetRotationPitch = CurrentDeltaRotation.Pitch * InScale * factor;
	DeltaRotation.Pitch += FMath::FInterpTo(DeltaRotation.Pitch, TargetRotationPitch, UGameplayStatics::GetWorldDeltaSeconds(this),2);
	
}

void AVehicleBase::TurnRight(float InScale)
{
	float TargetRotationYaw = CurrentDeltaRotation.Pitch * InScale;
	DeltaRotation.Yaw += FMath::FInterpTo(DeltaRotation.Yaw, TargetRotationYaw, UGameplayStatics::GetWorldDeltaSeconds(this), 2);
}

void AVehicleBase::MoveForward(float InScale)
{
	CurrentMoveScale = GetActorForwardVector()*InScale;
	
}

void AVehicleBase::TickMovement(float DeltaSecond)
{
	// add input vector
	AddMovementInput(CurrentMoveScale);
	SetActorRotation(GetActorRotation() + CurrentDeltaRotation * DeltaSecond);
	// add rotation

}