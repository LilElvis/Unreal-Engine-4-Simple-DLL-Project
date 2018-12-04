MAKING C++ DLL

- Open VS Professional 2017

- Create a new project

- Click Windows Desktop

- Choose 'Windows Desktop Wizard'

- Choose save directory

- Click 'OK'

- Select '.dll' from the dropdown list

- Checkmark 'Empty Project'

- Uncheck Precompiled Headers and SDL Checks

- Click 'OK'

- Create 'Wrapper.h' and 'Wrapper.cpp'

- IN THE HEADER

- Include any classes you wish to wrap the functions of

- Create a macro to mark functions for export:

#define DLL_EXPORT __declspec(dllexport)

- Declare any lists of class objects you may need to manage within the DLL

- Check if this is defined in c++, and if so, delare it in C:

#ifdef __cplusplus
extern "C" {
#endif

	//Put function declarations here

#ifdef __cplusplus
}
#endif

- This avoids names changing when compiled

- Use macro before each declaration, and declare functions to be exported 

- IN THE SOURCE:

- #pragama once and #include "Wrapper.h"

- Define all functions for export, if you are using external functions from a class, call the functions from 
DLL managed objects within these functions

- Ensure your compiler is set to 'Release' and 'x64'

- Click 'Build'

- Ignore error popups, check the compiler to verify the build succeeded

- Retrieve your built DLL and place in your Unreal project

MAKING UNREAL PROJECT AND IMPORTING DLLS

- Create new Unreal Project with C++

- Click no starter content

- IN THE PROJECT FILES:

- Create a folder called 'Plugins'

- Create a folder named 'DLLs' within 'Plugins'

- Drag built DLL into the 'DLLs' folder

- IN THE EDITOR:

- Create a new C++ Class to load DLLs

- Inherit from BlueprintFunctionLibrary

- IN THE HEADER:

- If there are errors, rescan the solution, GENERATED_BODY is created when the 
code is compiled in the editor for the first time

- Change '#include' from CoreMinimal.h to Core.h

- After GENERATED_BODY(), make the space public

- Write UFUNCTION(BlueprintCallable, Category = "DLL Tut Library")

- This will go before each function to add them to the blueprint library

- Write 'static' followed by the return value of your function and then name the 
function

- Declare an 'importDLL' function taking in an FString for the folder and filename, 
it should return a bool

- Declare a 'freeDLL' function, it should return void

- Declare an 'import' and wrapper function for each of the functions in the DLL

- The 'import' functions should return bools, and the wrapper functions should 
return the same type their DLL counterpart does, or the equivalent Unreal type

- IN THE SOURCE:

- #include "PojectName.h"

- typedef a function pointer for every function to be imported

- Create an object of every function pointer to store the imported functions in

- In importDLL, use *FPaths library to generate a relative file path to the plugin directory

- Use FPlatformProcess to get the DLL handle from the dereferenced file path

- In freeDll, nullify all the function objects, and use FPlatformProcess to free the DLL handle

- In each import function, use FPlatformProcess to get the DLL export from the DLL handle with the exact name 
of the function

- Cast the result as the function's respective pointer, and store it in the respective object

- In each wrapper funtion, pass parameters from Unreal to the function pointer object and return the result

- BACK IN THE EDITOR

- Compile the code and fix any errors

- Create a new blueprint class to call your functions in

- Open event graph, call all functions and push success/error messages on BeginPlay

- Ensure every string is spelled properly, and you remember the file extension when giving the name of your file

- Drag actor into scene

- Press play

- PACKAGING THE PROJECT

- If you need to package a build, ensure that you make a "Plugins" folder next to the "Content" folder in the 
packaged game directory, and include your DLLs in the same file structure