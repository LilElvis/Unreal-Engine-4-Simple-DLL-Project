#pragma once

#define DLL_EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

	DLL_EXPORT char* testFunction();

#ifdef __cplusplus
}
#endif