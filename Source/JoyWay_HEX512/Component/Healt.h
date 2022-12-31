// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Healt.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAY_HEX512_API UHealt : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealt();

	UFUNCTION()
	void TakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDestroyedActor = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SetupHealt = 100;

	UPROPERTY(BlueprintReadWrite);
	int CurrentHealt;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
