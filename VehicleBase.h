// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VehicleBase.generated.h"




UCLASS()
class DEMO_API AVehicleBase : public ACharacter
{
	GENERATED_BODY()


public:
	
	typedef ACharacter Super;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl")
		float BaseLookUpRate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl")
		float BaseLookRightRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl")
		FRotator CurrentDeltaRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl")
		FVector CurrentMoveScale;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl")
	//	float BaseTurnRightRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl")
		float Deceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementControl")
		bool bInversePitch;

	

	UPROPERTY(BlueprintReadOnly)
		UCharacterMovementComponent* CharacterMovementComponent;

	//transient data
	//degree per second
	UPROPERTY(Transient, BlueprintReadWrite)
		FRotator DeltaRotation;


	//
	//
public:

	void BrakePress();

	void BrakeUnpress();

	void ControllerLookup(float InScale);

	void ControllerLookRight(float InScale);

	void TurnUp(float InScale);

	void TurnRight(float InScale);

	void MoveForward(float InScale);

	void TickMovement(float DeltaSecond);

	//
public:
	// Sets default values for this character's properties
	AVehicleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
