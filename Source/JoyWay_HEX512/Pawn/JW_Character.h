// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "JoyWay_HEX512/Component/CameraTrace.h"
#include "JoyWay_HEX512/Component/Healt.h"
#include "JW_Character.generated.h"

UCLASS()
class JOYWAY_HEX512_API AJW_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJW_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere);
	USpringArmComponent* HandLeftArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	USpringArmComponent* HandLeftArm_Weapon;

	UPROPERTY(EditAnywhere);
	USpringArmComponent* HandRightArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	USpringArmComponent* HandRightArm_Weapon;

	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraTrace* CameraTraceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealt* HealtComponent;

	UPROPERTY(BlueprintReadWrite)
	AActor* WeaponFirst;

	UPROPERTY(BlueprintReadWrite)
	AActor* WeaponSecond;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LockUpRate = 45.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnRate = 45.f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Turn(float Axis);
	virtual void LookUp(float Axis);
	virtual void MoveForward(float Axis);
	virtual void MoveRight(float Axis);

	virtual void Fire();
	virtual void FireReleased();
	virtual void Aim();
	virtual void AimReleased();
	virtual void Reload();
	virtual void ReloadReleased();
	virtual void Take();
	virtual void TakeReleased();
};
