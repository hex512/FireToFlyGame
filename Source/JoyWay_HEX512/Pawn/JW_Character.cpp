// Fill out your copyright notice in the Description page of Project Settings.


#include "JW_Character.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "JoyWay_HEX512/interfaces/InteractHelper.h"
#include "JoyWay_HEX512/Interfaces/WeaponHelper.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AJW_Character::AJW_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->SetJumpAllowed(true);
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 540.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraTraceComponent = CreateDefaultSubobject<UCameraTrace>("CameraTraceComponent");
	HealtComponent = CreateDefaultSubobject<UHealt>("HealtComponent");

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetMesh(), NAME_None);

	HandLeftArm = CreateDefaultSubobject<USpringArmComponent>("HandLeftArm");
	HandLeftArm->SetupAttachment(PlayerCamera, USpringArmComponent::SocketName);
	HandLeftArm->SetRelativeRotation(FRotator(0,-180,0));
	HandLeftArm->SetRelativeLocation(FVector(0,-26,-23));
	HandLeftArm->bDoCollisionTest = false;
	HandLeftArm->TargetArmLength = 23.f;

	HandLeftArm_Weapon = CreateDefaultSubobject<USpringArmComponent>("HandLeftArm_Weapon");
	HandLeftArm_Weapon->SetupAttachment(HandLeftArm, USpringArmComponent::SocketName);
	HandLeftArm_Weapon->SetRelativeRotation(FRotator(0,90,0));
	HandLeftArm_Weapon->SetRelativeLocation(FVector(0,0,0));
	HandLeftArm_Weapon->bDoCollisionTest = false;
	HandLeftArm_Weapon->TargetArmLength = 0.f;
	HandLeftArm_Weapon->bEnableCameraRotationLag = true;
	HandLeftArm_Weapon->CameraRotationLagSpeed = 59.f;

	HandRightArm = CreateDefaultSubobject<USpringArmComponent>("HandRightArm");
	HandRightArm->SetupAttachment(PlayerCamera, USpringArmComponent::SocketName);
	HandRightArm->SetRelativeRotation(FRotator(0,-180,0));
	HandRightArm->SetRelativeLocation(FVector(0,26,-23));
	HandRightArm->bDoCollisionTest = false;
	HandRightArm->TargetArmLength = 23.f;

	HandRightArm_Weapon = CreateDefaultSubobject<USpringArmComponent>("HandRightArm_Weapon");
	HandRightArm_Weapon->SetupAttachment(HandRightArm, USpringArmComponent::SocketName);
	HandRightArm_Weapon->SetRelativeRotation(FRotator(0,90,0));
	HandRightArm_Weapon->SetRelativeLocation(FVector(0,0,0));
	HandRightArm_Weapon->bDoCollisionTest = false;
	HandRightArm_Weapon->TargetArmLength = 0.f;
	HandRightArm_Weapon->bEnableCameraRotationLag = true;
	HandRightArm_Weapon->CameraRotationLagSpeed = 59.f;
}

// Called when the game starts or when spawned
void AJW_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJW_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJW_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &AJW_Character::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AJW_Character::LookUp);
	PlayerInputComponent->BindAxis("MoveForward", this, &AJW_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJW_Character::MoveRight);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AJW_Character::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AJW_Character::FireReleased);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AJW_Character::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AJW_Character::AimReleased);
	
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AJW_Character::Reload);
	PlayerInputComponent->BindAction("Reload", IE_Released, this, &AJW_Character::ReloadReleased);
	
	PlayerInputComponent->BindAction("Take", IE_Pressed, this, &AJW_Character::Take);
	PlayerInputComponent->BindAction("Take", IE_Released, this, &AJW_Character::TakeReleased);

}

void AJW_Character::Turn(float Axis)
{
	const float Yaw = Axis * .75f;
	AddControllerYawInput(Yaw);
}

void AJW_Character::LookUp(float Axis)
{
	const float Pitch = Axis * .75f;
	AddControllerPitchInput(Pitch);
}

void AJW_Character::MoveForward(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector Direction = UKismetMathLibrary::GetForwardVector(YawRotation);
	AddMovementInput(Direction, Axis);
}

void AJW_Character::MoveRight(float Axis)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector Direction = UKismetMathLibrary::GetRightVector(YawRotation);
	
	AddMovementInput(Direction, Axis);
}

void AJW_Character::Fire()
{
	if(IsValid(WeaponSecond))
	{
		if(WeaponSecond->Implements<UWeaponHelper>())
		{
			IWeaponHelper::Execute_Fire(WeaponSecond);
		}
	}
	else
	{
		if(IsValid(WeaponFirst))
		{
			if(WeaponFirst->Implements<UWeaponHelper>())
			{
				IWeaponHelper::Execute_Fire(WeaponFirst);
			}
		}
	}
}

void AJW_Character::FireReleased()
{
}

void AJW_Character::Aim()
{
	if(IsValid(WeaponFirst))
	{
		if(WeaponFirst->Implements<UWeaponHelper>())
		{
			IWeaponHelper::Execute_Fire(WeaponFirst);
		}
	}
	// if(IsValid(Weapon))
	// {
	// 	if(Weapon->Implements<UWeaponHelper>())
	// 	{
	// 		IWeaponHelper::Execute_Aim(Weapon);
	// 	}
	// }
}

void AJW_Character::AimReleased()
{
}

void AJW_Character::Reload()
{
	if(IsValid(WeaponFirst))
	{
		if(WeaponFirst->Implements<UWeaponHelper>())
		{
			IWeaponHelper::Execute_Reload(WeaponFirst);
		}
	}
}

void AJW_Character::ReloadReleased()
{
}

void AJW_Character::Take()
{
	if(IsValid(CameraTraceComponent->LockAtActor))
	{
		if(CameraTraceComponent->LockAtActor->Implements<UInteractHelper>())
		{
			IInteractHelper::Execute_Take(CameraTraceComponent->LockAtActor, this);
		}
	}
}

void AJW_Character::TakeReleased()
{
}

