#pragma once
#include "includes.h"

bool InitGetKeys()
{
	HMODULE API = GetModuleHandle(skCrypt_(TEXT("win32u.dll")));
	if (API != NULL)
	{
		o_getasynckeystate = (LPFN_MBA)GetProcAddress(API, skCrypt_("NtUserGetAsyncKeyState"));
		if (o_getasynckeystate != NULL)
			return true;
		else
			return false;
	}
}

VOID Main() {

	MH_Initialize();

	#ifdef DEBUG
		Utilities::CreateConsole();
	#endif // DEBUG

	if (!InitGetKeys()) { Warn(skCrypt("InitGetKeys failed")); return; }
	
}