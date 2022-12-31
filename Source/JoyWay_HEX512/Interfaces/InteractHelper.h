// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractHelper.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractHelper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JOYWAY_HEX512_API IInteractHelper
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interact")
	void Take(APawn* Pawn);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interact")
	void Focus();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interact")
	void Unfocus();
};
