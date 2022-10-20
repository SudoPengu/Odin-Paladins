#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024
#define skCrypt(str) _xor_(str).c_str()
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))
#define MAKE_IMU32(r, g, b, a) ((a << 24) + (b << 16) + (g << 8) + r)

// Create console and print debug stuff. Comment to disable.
//#define DEBUG

#include <d3d11.h>

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include "xorstr.hpp"
#include <math.h>
#include <codecvt>
#include <Psapi.h>
#include <list>
#include <timeapi.h>
#include <winnt.h>

#pragma comment(lib,"Kernel32.lib")
#pragma comment(lib,"Winmm.lib")

#include <MinHook.h>
#pragma comment(lib, "minhook.lib")

#include "detours/detours.h"
#include "lazyimporter.h"
#include "MainOptions.h"
#include "CheatHelper.h"
#include "Exploits.h"
#include "renderer/imgui.h"
#include "renderer/imgui_impl_dx11.h"
#include "renderer/imgui.h"
#include "renderer/imgui_internal.h"
#include "renderer/color.h"
#include "dynamicimports.h"
#include "SDK/Helpers/OffsetsDefines.h"
#include "SDK/PL_Engine_classes.h"

std::string Warn(std::string warningText) {
    MessageBoxA((HWND)0, (LPCSTR)(warningText.c_str()), (LPCSTR)skCrypt("Warning"), (UINT)0);
    return warningText;
}