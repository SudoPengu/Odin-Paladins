#pragma once

// Dummies
class UObject;
class UFunction;

template<class T>
struct TAntiCheatArray;

class FNameEntry;

// ProcessEvent hook
typedef void(__thiscall* tProcessEvent)(UObject* pObject, UFunction* pFunction, const void* pParams, __int64 pResult);
extern tProcessEvent ProcessEvent;

// TAC GObjects / GNames
extern TAntiCheatArray<UObject*>* GlobalObjects;
extern TAntiCheatArray<FNameEntry*>* GlobalNames;