// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraTrace.generated.h"

USTRUCT()
struct FCameraTraceResult
{
	FCameraTraceResult(const FVector& CameraLocation, const FVector& CameraTarget, const FHitResult& Hit)
		: CameraLocation(CameraLocation),
		  CameraTarget(CameraTarget),
		  Hit(Hit)
	{}

	FCameraTraceResult(){};
	
	GENERATED_BODY()

	FVector CameraLocation;
	FVector CameraTarget;
	FHitResult Hit;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAY_HEX512_API UCameraTrace : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCameraTrace();

	UPROPERTY(BlueprintReadOnly)
	AActor* LockAtActor;

	UPROPERTY(BlueprintReadOnly)
	FVector LockAtView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Trace")
	float Distance = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Trace")
	bool bDebugMode = false;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	APawn* PawnCharacter = nullptr;
	
	FCameraTraceResult LineTraceScan() const;

	static void FocusActor(AActor* Actor, bool bIsFocus);
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
