// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadDLLs.h"
#include "SimpleDLLProject.h" //Include "ProjectName.h"

typedef char*(*_testFunction)(); //Make a function pointer for every function

_testFunction m_testFunction; //Make an object to store each function in

void* v_dllHandle; //Make a void pointer to store the DLL handle in

#pragma region Load DLL

bool ULoadDLLs::importDLL(FString folder, FString name)
{
	FString filePath = *FPaths::GamePluginsDir() + folder + "/" + name; //Composite a relative file path

	if (FPaths::FileExists(filePath)) //Check if the file at the path exists
	{
		v_dllHandle = FPlatformProcess::GetDllHandle(*filePath); //Get the DLL handle and store it
		if (v_dllHandle != NULL)
		{
			return true; //Successfully loaded a DLL
		}
	}
	return false; //Return an error
}

#pragma endregion Load DLL

#pragma region Import Methods

bool ULoadDLLs::importMethodTestFunction()
{
	if (v_dllHandle != NULL)
	{
		m_testFunction = NULL; FString processName = "testFunction"; //Must be the exact name of the function in the DLL
		m_testFunction = (_testFunction)FPlatformProcess::GetDllExport(v_dllHandle, *processName); //Cast return value as the type of function pointer, and store in the corresponding object
		
		if (m_testFunction != NULL)
		{
			return true; //Successfully imported the method from a DLL
		}
	}
	return false; //Return an error
}

#pragma endregion Import Methods

#pragma region Wrapper Methods

FString ULoadDLLs::testFunction()
{
	if (m_testFunction != NULL)
	{
		char* returnChar = m_testFunction(); //Create a variable to store the result of the function in and call it

		return (ANSI_TO_TCHAR(returnChar)); //ANSI is char*, TCHAR is FString
	}
	return "Error, the test function was not yet imported.";
}

#pragma endregion Wrapper Methods

#pragma region Unload DLL

void ULoadDLLs::freeDLL()
{
	if (v_dllHandle != NULL)
	{
		m_testFunction = NULL; //Nullify all function pointer objects

		FPlatformProcess::FreeDllHandle(v_dllHandle); v_dllHandle = NULL; //Free the DLL handle and then nullify the pointer
	}
}

#pragma endregion Unload DLL