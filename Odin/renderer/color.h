#pragma once

#include "imgui.h"

namespace Colors
{
	ImU32 WhiteCl = ImGui::ColorConvertFloat4ToU32(ImVec4(255.0f, 255.0f, 255.0f, 255.0f));
	ImU32 LimeCL = ImGui::ColorConvertFloat4ToU32(ImVec4(0, 255.0f, 0, 255.0f));
	ImU32 CyanCL = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 255.0f, 255.0f, 255.0f));
	ImU32 YellowCL = ImGui::ColorConvertFloat4ToU32(ImVec4(255.0f, 255.0f, 0.0f, 255.0f));
	ImU32 RedCL = ImGui::ColorConvertFloat4ToU32(ImVec4(255.0f, 0.0f, 0.0f, 255.0f));
	ImU32 BlackCL = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 255.0f));
}