#include "includes.h"
#include "DrawMenu.h"
#include "MainHooking.h"
#include "Major.h"

DWORD ProcessID;
uintptr_t ModuleBase;


// That's the MainTick() it's called at every present update
// In there we do things like, actor loop, ESP, visuals, Exploits...
bool first = false;
void MainTick()
{
	time_t now = time(0);
	char* dt = ctime(&now);

	char TitleBuff[80];
	sprintf_s(TitleBuff, skCrypt_("Odin 3.0.0a | %s"), dt);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(5, 5), Colors::WhiteCl, TitleBuff);

	// MainAddress() is called at every MainTick() it's basically getting all the needed offsets for the cheat that are already defined in "CheatHelper.h".
	bool bUpdated = MainAddress();
	if (bUpdated)
	{
		Exploits();
		if (!IsValid((DWORD64)AcknowledgedPawn)) return;
		if (Settings.ESP.Players || Settings.Aimbot) doActorsLoop();
	}

	// Visual Aimbot FOV Circle
	if (Settings.Aimbot && Settings.ShowFOV)
	{
		ImVec2 c(width / 2, height / 2);
		float aimfov = (Settings.AimbotFOV + 1) * 20.0f;
		ImGui::GetOverlayDrawList()->AddCircle(c, aimfov, Colors::WhiteCl);
	}
}


// DllMain. That's the entry point of our DLL, it's executed when we inject the DLL into the game.
BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	HANDLE m_timer;
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(module);

		ProcessID = GetCurrentProcessId();
		ModuleBase = (uintptr_t)GetModuleHandle(0);

		// This is initializing the settings and the needed hooks (Main())
		SettingsHelper::Initialize();
		Main();

		// DX11 PresentScene hook
		DYNAMIC_FUNCTION(CreateTimerQueueTimer,
			(skCrypt_("KERNEL32.DLL")))(&m_timer, DYNAMIC_FUNCTION(CreateTimerQueue,
				(skCrypt_("KERNEL32.DLL")))(),
				reinterpret_cast<WAITORTIMERCALLBACK>(&Renderintial), nullptr, 1, NULL, NULL);
	}

	return TRUE;
}