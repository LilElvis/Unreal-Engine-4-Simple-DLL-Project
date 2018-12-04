//This is a tutorial for loading a DLL and importing a single function from it in UE4 for use in Blueprints - Raymond Dee, 100578667

#pragma once

#include "Core.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadDLLs.generated.h"

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
