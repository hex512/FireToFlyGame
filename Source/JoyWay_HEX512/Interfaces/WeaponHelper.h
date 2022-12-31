// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponHelper.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWeaponHelper : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JOYWAY_HEX512_API IWeaponHelper
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interact")
	void Fire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interact")
	void Aim();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interact")
	void Reload();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interact")
	int GetCurrentAmmo();
};
