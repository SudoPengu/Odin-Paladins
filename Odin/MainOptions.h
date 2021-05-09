#include "includes.h"

static ID3D11DeviceContext* m_pContext;
static ID3D11RenderTargetView* g_pRenderTargetView;
static IDXGISwapChain* g_pSwapChain;

static WNDPROC oWndProc;

typedef int (WINAPI* LPFN_MBA)(DWORD);
static LPFN_MBA o_getasynckeystate;

static HWND hWnd;

static bool ShowMenu = true;

typedef struct {
	bool Aimbot;
	int Aimkey;
	int AimPos;
	bool AimbotPrediction;
	bool AimbotSmoothing;
	float AimbotSmooth;
	float AimbotFOV;
	bool ShowFOV;
	bool NoSpread;
	bool NoRecoil;
	bool ThirdPerson;
	bool Speedhack;
	int Speed;
	float FOVValue;
	bool FOV;
	bool NameProtection;

	struct {
		bool Players;
		bool Glow;
		bool Name;
		bool Box;
		bool Tracer;
		bool Health;
	} ESP;
} SETTINGS;

SETTINGS Settings = { 0 };
namespace SettingsHelper {
	VOID Initialize() {
		Settings = { 0 };

		Settings.Aimbot = false;
		Settings.AimbotPrediction = false;
		Settings.Aimkey = 7;
		Settings.AimbotSmoothing = false;
		Settings.AimbotSmooth = 0.0f;
		Settings.AimbotFOV = 5.0f;
		Settings.AimPos = 0;
		Settings.ShowFOV = true;

		Settings.Speedhack = false;
		Settings.Speed = 3;

		Settings.NoSpread = false;
		Settings.NoRecoil = false;
		Settings.NameProtection = false;
		Settings.ThirdPerson = false;
		Settings.FOV = false;
		Settings.FOVValue = 50.0f;

		Settings.ESP.Players = false;
		Settings.ESP.Glow = false;
		Settings.ESP.Name = true;
		Settings.ESP.Box = true;
		Settings.ESP.Tracer = false;
		Settings.ESP.Health = false;

	}
}