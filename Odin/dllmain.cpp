#include "includes.h"
#include "DrawMenu.h"
#include "MainHooking.h"
#include "Major.h"

DWORD ProcessID;
uintptr_t ModuleBase;

bool first = false;
void MainTick()
{
	time_t now = time(0);
	char* dt = ctime(&now);

	char TitleBuff[80];
	sprintf_s(TitleBuff, skCrypt_("Odin Github | %s"), dt);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(5, 5), Colors::WhiteCl, TitleBuff);

	bool bUpdated = MainAddress();
	if (bUpdated)
	{
		Exploits();
		if (!IsValid((DWORD64)AcknowledgedPawn)) return;
		if (Settings.ESP.Players || Settings.Aimbot) doActorsLoop();
	}

	if (Settings.Aimbot && Settings.ShowFOV)
	{
		ImVec2 c(width / 2, height / 2);
		float aimfov = (Settings.AimbotFOV + 1) * 20.0f;
		ImGui::GetOverlayDrawList()->AddCircle(c, aimfov, Colors::WhiteCl);
	}
}


BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	HANDLE m_timer;
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(module);

		ProcessID = GetCurrentProcessId();
		ModuleBase = (uintptr_t)GetModuleHandle(0);

		SettingsHelper::Initialize();
		Main();

		DYNAMIC_FUNCTION(CreateTimerQueueTimer,
			(skCrypt_("KERNEL32.DLL")))(&m_timer, DYNAMIC_FUNCTION(CreateTimerQueue,
				(skCrypt_("KERNEL32.DLL")))(),
				reinterpret_cast<WAITORTIMERCALLBACK>(&Renderintial), nullptr, 1, NULL, NULL);
	}

	return TRUE;
}