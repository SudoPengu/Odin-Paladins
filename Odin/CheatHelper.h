#pragma once

#include "SDK/PL_Engine_classes.h"

#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

#define skCrypt_(str) _xor_(str).c_str()
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))


HWND hWindow = 0;
bool bHidden = false;

float width = 0;
float height = 0;

// Present hook
HRESULT(*PresentOriginal)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*ResizeOriginal)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

// QPC Hook
static BOOL(WINAPI* originalQueryPerformanceCounter)(LARGE_INTEGER* performanceCounter) = QueryPerformanceCounter;
static DWORD(WINAPI* originalGetTickCount)() = GetTickCount;
static ULONGLONG(WINAPI* originalGetTickCount64)() = GetTickCount64;
static DWORD(WINAPI* originalTimeGetTime)() = timeGetTime;

static bool firstTime = true;

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;

static float FOV;

// Main addresses
DWORD_PTR                Engine;
UEngine*                 Game;
ULocalPlayer*            LocalPlayer;
APlayerController*       PlayerController;
APlayerReplicationInfo*  ReplicationInfo;
APawn*                   AcknowledgedPawn;
ACamera*                 PlayerCamera;
AWorldInfo*              WorldInfo;
ATgDevice*               Weapon;

// Aimkey dropdown
DWORD keys[] = { VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9 };
const char* keyItems[] = { "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse", "Numpad 1", "Numpad 2", "Numpad 3", "Numpad 4", "Numpad 5", "Numpad 6", "Numpad 7", "Numpad 8", "Numpad 9" };

int bones[] = { 0, 30 };
const char* boneItems[] = { "Head", "Body" };

BOOL IsValid(DWORD64 address)
{
	if (!IsBadReadPtr((const void*)address, (UINT_PTR)8)) return TRUE;
	else return FALSE;
}

bool GetAimKey()
{
	return GetAsyncKeyState(keys[Settings.Aimkey]);
}

extern std::string Warn(std::string warningText);