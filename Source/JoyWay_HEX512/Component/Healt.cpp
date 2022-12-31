// Fill out your copyright notice in the Description page of Project Settings.


#include "Healt.h"

#include "JoyWay_HEX512/Interfaces/HealtHelper.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UHealt::UHealt()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealt::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(GetOwner()))
	{
		CurrentHealt = SetupHealt;
		GetOwner()->OnTakePointDamage.AddDynamic(this, &UHealt::TakePointDamage);
	}
}

void UHealt::TakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
	UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType,
	AActor* DamageCauser)
{
	const int CurrentDamage = UKismetMathLibrary::FTrunc(Damage);

	CurrentHealt = CurrentHealt - CurrentDamage;

	if(CurrentHealt <= 0)
	{
		//Dead
		if(GetOwner()->Implements<UHealtHelper>())
		{

			GetOwner()->OnTakePointDamage.RemoveDynamic(this, &UHealt::TakePointDamage);
			IHealtHelper::Execute_Dead(GetOwner());
		}
	}
	else
	{
		//Hit reaction etc
		if(GetOwner()->Implements<UHealtHelper>())
		{
			IHealtHelper::Execute_Hit(GetOwner(), ShotFromDirection);
		}
	}
	
}

