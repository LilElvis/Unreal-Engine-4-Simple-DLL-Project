// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadDLLs.generated.h"

/**
This is a simple test project to find the bare minimum required to load a DLL that works into Unreal Engine 4
 */

UCLASS()
class SIMPLEDLLPROJECT_API ULoadDLLs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "DLL Library") static bool importDLL(FString folder, FString name);
		
	UFUNCTION(BlueprintCallable, Category = "DLL Library") static bool importMethodTestFunction();

	UFUNCTION(BlueprintCallable, Category = "DLL Library") static FString testFunction();
	
	UFUNCTION(BlueprintCallable, Category = "DLL Library") static void freeDLL();
};
