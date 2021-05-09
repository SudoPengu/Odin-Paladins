#pragma once
#include "stdafx.h"
#define RELATIVE_ADDR(addr, size) ((PBYTE)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))

namespace Utilities {
	VOID CreateConsole();
	VOID KillConsole();
}