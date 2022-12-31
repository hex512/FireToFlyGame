// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrace.h"

#include "JoyWay_HEX512/interfaces/InteractHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCameraTrace::UCameraTrace()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraTrace::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(GetOwner()))
	{
		PawnCharacter = Cast<APawn>(GetOwner());
		
		if(!IsValid(PawnCharacter)) //If else for player controller attach component
		{
			PawnCharacter = Cast<AController>(GetOwner())->GetPawn();
		}
	}
}


FCameraTraceResult UCameraTrace::LineTraceScan() const
{
	const EDrawDebugTrace::Type DrawDebug = bDebugMode == 1 ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;
	
	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
			
	const FVector CameraLocation = CameraManager->GetCameraLocation();
	const FVector CameraForwardVector = CameraManager->GetActorForwardVector();
	const FVector CameraTarget = UKismetMathLibrary::Multiply_VectorFloat(CameraForwardVector, Distance);
	
	TArray<AActor*> ActorsIgnore;
	GetOwner()->GetAllChildActors(ActorsIgnore, true);

	FHitResult LineTraceSingleResult;
	UKismetSystemLibrary::LineTraceSingle(this,
										  CameraLocation,
										  UKismetMathLibrary::Add_VectorVector(CameraLocation, CameraTarget),
										  ETraceTypeQuery::TraceTypeQuery1, false, ActorsIgnore,
										  DrawDebug, LineTraceSingleResult, true,
										  FLinearColor(1.0,0.0,0.0,1.0),
										  FLinearColor(0.0,1.0,0.0,1.0),
										  0.f);

	return FCameraTraceResult(CameraLocation, CameraTarget, LineTraceSingleResult);
}

void UCameraTrace::FocusActor(AActor* Actor, bool bIsFocus)
{
	if(IsValid(Actor))
	{
		if(Actor->Implements<UInteractHelper>())
		{
			if(bIsFocus)
			{
				IInteractHelper::Execute_Focus(Actor);
			}
			else
			{
				IInteractHelper::Execute_Unfocus(Actor);
			}
		}
	}
}

// Called every frame
void UCameraTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(IsValid(PawnCharacter))
	{
		if(PawnCharacter->IsLocallyControlled() && PawnCharacter->IsPlayerControlled())
		{
			
			const FCameraTraceResult TraceResult = LineTraceScan();

			if(TraceResult.Hit.bBlockingHit)
			{
				LockAtView = TraceResult.Hit.ImpactPoint;

				if(UKismetMathLibrary::Vector_Distance(TraceResult.CameraLocation, LockAtView) <= UKismetMathLibrary::Vector_Distance(TraceResult.CameraLocation, GetOwner()->GetActorLocation()))
				{
					LockAtView = UKismetMathLibrary::Add_VectorVector(TraceResult.CameraLocation, TraceResult.CameraTarget);
				}
			}
			else
			{
				LockAtView = UKismetMathLibrary::Add_VectorVector(TraceResult.CameraLocation, TraceResult.CameraTarget);
			}

			const float Lenght = UKismetMathLibrary::Vector_Distance(PawnCharacter->GetActorLocation(), LockAtView);
			if(IsValid(TraceResult.Hit.Actor.Get()) && Lenght <= Distance)
			{
				if(TraceResult.Hit.Actor.Get() != LockAtActor)
				{
					FocusActor(TraceResult.Hit.Actor.Get(), true);
					FocusActor(LockAtActor, false);
				}
				
				LockAtActor = TraceResult.Hit.Actor.Get();
				
			}
			else
			{

				FocusActor(LockAtActor, false);
				LockAtActor = nullptr;
			}
		}
	}
}

