#include "stdafx.h"
#include <iostream>

#include "xorstr.hpp"
#define skCrypt_(str) _xor_(str).c_str()

namespace Utilities {
	VOID CreateConsole() {
		AllocConsole();
		static_cast<VOID>(freopen(skCrypt_("CONIN$"), skCrypt_("r"), stdin));
		static_cast<VOID>(freopen(skCrypt_("CONOUT$"), skCrypt_("w"), stdout));
		static_cast<VOID>(freopen(skCrypt_("CONOUT$"), skCrypt_("w"), stderr));
	}

	VOID KillConsole() {
		FreeConsole();
	}
}