#pragma once
#include "includes.h"
#define E(str) skCrypt_(str)


void MainTick();
void DrawMenu()
{
	if (o_getasynckeystate((DWORD)VK_INSERT) == -32767) ShowMenu = !ShowMenu;
	if (o_getasynckeystate((DWORD)VK_F1) == -32767) Settings.Aimbot = !Settings.Aimbot;
	if (o_getasynckeystate((DWORD)VK_F2) == -32767) Settings.ESP.Players = !Settings.ESP.Players;
	if (o_getasynckeystate((DWORD)VK_F3) == -32767)
	{
		Settings.NoSpread = !Settings.NoSpread;
		Settings.NoRecoil = !Settings.NoRecoil;
	}
	if (o_getasynckeystate((DWORD)VK_F4) == -32767) Settings.ThirdPerson = !Settings.ThirdPerson;
	if (o_getasynckeystate((DWORD)VK_F5) == -32767) Settings.Speedhack = !Settings.Speedhack;

	if (ShowMenu)
	{
		bHidden = false;
		ImGui::StyleColorsDark();

		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
		colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);

		style->ChildRounding = 4.0f;
		style->FrameBorderSize = 1.0f;
		style->FrameRounding = 2.0f;
		style->GrabMinSize = 7.0f;
		style->PopupRounding = 2.0f;
		style->ScrollbarRounding = 12.0f;
		style->ScrollbarSize = 13.0f;
		style->WindowRounding = 4.0f;

		std::string title = E("Odin Private | Xiloe#7399");
		ImGuiWindowFlags TargetFlags;
		TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

		if (ImGui::Begin(title.c_str(), 0, ImVec2(360, 570), -1.f, TargetFlags)) {
			ImVec2 ve = ImVec2(ImGui::GetItemRectMin().x + 180, ImGui::GetItemRectMin().y + 40);
			ImVec2 v = ImVec2(ImGui::GetItemRectMax().x - 15, ImGui::GetItemRectMax().y + 290);

			ImGui::Text(E("[+] Combat"));
			ImGui::Checkbox(E("Aimbot (F1)"), &Settings.Aimbot);
			if (Settings.Aimbot)
			{
				ImGui::Checkbox(E("Projectile Prediction"), &Settings.AimbotPrediction);
				ImGui::Checkbox(E("Show FOV"), &Settings.ShowFOV);
				ImGui::Combo(E("Aimbot Key"), &Settings.Aimkey, keyItems, IM_ARRAYSIZE(keyItems));
				ImGui::Combo(E("Aimbot Bone"), &Settings.AimPos, boneItems, IM_ARRAYSIZE(boneItems));
				ImGui::SliderFloat(E("FOV"), &Settings.AimbotFOV, 0.5f, 50.0f);
				/*ImGui::Checkbox(E("Smoothing"), &Settings.AimbotSmoothing);
				if (&Settings.AimbotSmoothing)
					ImGui::SliderFloat(E("Smooth"), &Settings.AimbotSmooth, 0.0f, 1.0f);*/
			}

			ImGui::Text(E(""));
			ImGui::Text(E("[+] Visuals"));
			ImGui::Checkbox(E("Players ESP (F2)"), &Settings.ESP.Players);
			if (Settings.ESP.Players)
			{
				ImGui::Checkbox(E("Glow ESP"), &Settings.ESP.Glow);
				ImGui::Checkbox(E("Box ESP"), &Settings.ESP.Box);
				ImGui::Checkbox(E("Name ESP"), &Settings.ESP.Name);
				ImGui::Checkbox(E("Health ESP"), &Settings.ESP.Health);
				ImGui::Checkbox(E("Tracer ESP"), &Settings.ESP.Tracer);
			}

			ImGui::Text(E(""));
			ImGui::Text(E("[+] Exploits"));
			ImGui::Checkbox(E("No Spread (F3)"), &Settings.NoSpread);
			ImGui::Checkbox(E("No Recoil (F3)"), &Settings.NoRecoil);
			ImGui::Checkbox(E("Third Person (F4)"), &Settings.ThirdPerson);
			ImGui::Checkbox(E("FOV Slider"), &Settings.FOV);
			ImGui::Text(E(""));
			if (Settings.FOV)
				ImGui::SliderFloat(E("FOV Slider"), &Settings.FOVValue, 20.0f, 150.0f);

			ImGui::Text(E(""));
			if (!Settings.Speedhack)
			{
				ImGui::Text(E("Speed"));
				ImGui::SliderInt(E(""), &Settings.Speed, 1, 5);
			}
			ImGui::Checkbox(E("Speedhack (F5)"), &Settings.Speedhack);
		}
		ImGui::End();
	} else
		bHidden = true;
}


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
__declspec(dllexport) LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ShowMenu) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return TRUE;
	}

	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}


bool once = true;
_declspec(dllexport) HRESULT PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
	static HWND hWnd = 0;

	if (firstTime) {

		if (!device) {
			swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
			device->GetImmediateContext(&immediateContext);

			DXGI_SWAP_CHAIN_DESC desc;
			swapChain->GetDesc(&desc);

			ID3D11Texture2D* renderTarget = nullptr;
			if (SUCCEEDED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget)))
			{
				device->CreateRenderTargetView(renderTarget, NULL, &renderTargetView);
				renderTarget->Release();
				device->Release();

				ID3D11Texture2D* backBuffer = 0;
				swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&backBuffer);
				D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
				backBuffer->GetDesc(&backBufferDesc);

				hWnd = FindWindow((L"LaunchUnrealUWindowsClient"), (L"Paladins (64-bit, DX11)"));
				if (!width) {
					oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcHook)));
				}

				width = (float)backBufferDesc.Width;
				height = (float)backBufferDesc.Height;
				backBuffer->Release();

				ImGui_ImplDX11_Init(desc.OutputWindow, device, immediateContext);
				ImGui_ImplDX11_CreateDeviceObjects();
			}
		
		}
		firstTime = false;
	}

	if (renderTargetView)
	{
		immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
		ImGui_ImplDX11_NewFrame();
	

			MainTick();

			DrawMenu();

			
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	
	return PresentOriginal(swapChain, syncInterval, flags);
}


__declspec(dllexport) HRESULT ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	immediateContext->Release();
	device->Release();
	device = nullptr;

	return ResizeOriginal(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}
bool Renderintial()
{
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context))) {
		MessageBox(0, L"Failed to create D3D11 device and swap chain", L"Failure", MB_ICONERROR);
		return FALSE;
	}

	auto table = *reinterpret_cast<PVOID**>(swapChain);
	auto present = table[8];
	auto resize = table[13];

	context->Release();
	device->Release();
	swapChain->Release();

	MH_CreateHook(present, PresentHook, reinterpret_cast<PVOID*>(&PresentOriginal));
	MH_EnableHook(present);

	MH_CreateHook(resize, ResizeHook, reinterpret_cast<PVOID*>(&ResizeOriginal));
	MH_EnableHook(resize);

	return TRUE;
}