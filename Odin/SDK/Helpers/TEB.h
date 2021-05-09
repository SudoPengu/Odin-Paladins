#pragma once
#include "ntapi.h"
#include "../../Globals.h"

HANDLE GetFirstThread();
uintptr_t StealTLS();
uintptr_t GetXorKey(size_t index);