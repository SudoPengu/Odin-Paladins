#pragma once
#include "includes.h"
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "Globals.h"

#define Const_URotation180        32768
#define Const_PI                  3.14159265358979323
#define Const_RadToUnrRot         10430.3783504704527
#define Const_UnrRotToRad         0.00009587379924285
#define Const_URotationToRadians  Const_PI / Const_URotation180 

namespace maths
{
	FRotator VectorToRotation(FVector vVector)
	{
		FRotator rRotation;

		rRotation.Yaw = atan2(vVector.Y, vVector.X) * Const_RadToUnrRot;
		rRotation.Pitch = atan2(vVector.Z, sqrt((vVector.X * vVector.X) + (vVector.Y * vVector.Y))) * Const_RadToUnrRot;
		rRotation.Roll = 0;

		return rRotation;
	}

	FVector RotationToVector(FRotator R)
	{
		FVector Vec;
		float fYaw = R.Yaw * Const_URotationToRadians;
		float fPitch = R.Pitch * Const_URotationToRadians;
		float CosPitch = cos(fPitch);
		Vec.X = cos(fYaw) * CosPitch;
		Vec.Y = sin(fYaw) * CosPitch;
		Vec.Z = sin(fPitch);
		return Vec;
	}

	float VectorMagnitude(FVector Vec) {
		return sqrt((Vec.X * Vec.X) + (Vec.Y * Vec.Y) + (Vec.Z * Vec.Z));
	}

	void Normalize(FVector& v)
	{
		float size = VectorMagnitude(v);

		if (!size)
		{
			v.X = v.Y = v.Z = 1;
		}
		else
		{
			v.X /= size;
			v.Y /= size;
			v.Z /= size;
		}
	}


	void GetAxes(FRotator R, FVector& X, FVector& Y, FVector& Z)
	{
		X = RotationToVector(R);
		Normalize(X);
		R.Yaw += 16384;
		FRotator R2 = R;
		R2.Pitch = 0.f;
		Y = RotationToVector(R2);
		Normalize(Y);
		Y.Z = 0.f;
		R.Yaw -= 16384;
		R.Pitch += 16384;
		Z = RotationToVector(R);
		Normalize(Z);
	}

	FVector VectorSubtract(FVector s1, FVector s2)
	{
		FVector temp;
		temp.X = s1.X - s2.X;
		temp.Y = s1.Y - s2.Y;
		temp.Z = s1.Z - s2.Z;

		return temp;
	}

	FVector VectorAdd(FVector s1, FVector s2)
	{
		FVector temp;
		temp.X = s1.X + s2.X;
		temp.Y = s1.Y + s2.Y;
		temp.Z = s1.Z + s2.Z;

		return temp;
	}

	FVector VectorScale(FVector s1, float scale)
	{
		FVector temp;
		temp.X = s1.X * scale;
		temp.Y = s1.Y * scale;
		temp.Z = s1.Z * scale;

		return temp;
	}

	float VectorDotProduct(const FVector& A, const FVector& B)
	{
		float tempx = A.X * B.X;
		float tempy = A.Y * B.Y;
		float tempz = A.Z * B.Z;

		return (tempx + tempy + tempz);
	}

	ImVec2 FV2D2ImVec2(FVector2D fvec)
	{
		ImVec2 imvec;
		imvec.x = fvec.X;
		imvec.y = fvec.Y;

		return imvec;
	}

	void AimAtVector(FVector TargetVec, FVector PlayerLocation, FRotator& AimRot)
	{
		FVector AimVec;
		AimVec.X = TargetVec.X - PlayerLocation.X;
		AimVec.Y = TargetVec.Y - PlayerLocation.Y;
		AimVec.Z = TargetVec.Z - PlayerLocation.Z;

		FRotator AimAtRot = VectorToRotation(AimVec);
		AimRot = AimAtRot;
	}

	FVector GetAngleTo(FVector TargetVec, FVector OriginVec)
	{
		FVector Diff;
		Diff.X = TargetVec.X - OriginVec.X;
		Diff.Y = TargetVec.Y - OriginVec.Y;
		Diff.Z = TargetVec.Z - OriginVec.Z;

		return Diff;
	}

	float GetDistance(FVector to, FVector from) {
		float deltaX = to.X - from.X;
		float deltaY = to.Y - from.Y;
		float deltaZ = to.Z - from.Z;

		return (float)sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
	}

	float GetCrosshairDistance(float Xx, float Yy, float xX, float yY)
	{
		return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
	}
}

// can be better but I'll let you do it :)
bool W2S(FVector target, ImVec2& dst, FRotator myRot, FVector myLoc, float fov)
{
	FVector AxisX, AxisY, AxisZ, Delta, Transformed;
	maths::GetAxes(myRot, AxisX, AxisY, AxisZ);

	Delta = maths::VectorSubtract(target, myLoc);
	Transformed.X = maths::VectorDotProduct(Delta, AxisY);
	Transformed.Y = maths::VectorDotProduct(Delta, AxisZ);
	Transformed.Z = maths::VectorDotProduct(Delta, AxisX);

	if (Transformed.Z < 1.00f)
		Transformed.Z = 1.00f;

	float GFOV = fov;
	float CentX = (width / 2.0f);
	float CentY = (height / 2.0f);

	dst.x = CentX + Transformed.X * (CentX / tan(GFOV * Const_PI / 360.0f)) / Transformed.Z;
	dst.y = CentY + -Transformed.Y * (CentX / tan(GFOV * Const_PI / 360.0f)) / Transformed.Z;

	if (dst.x >= 0.0f && dst.x <= width)
	{
		if (dst.y >= 0.0f && dst.y <= height)
		{
			return true;
		}
	}
	return false;
}

// Current locked pawn
APawn* LockedPawn = nullptr;
FVector LockedHead = FVector{ 0, 0, 0 };
bool Locked = false;

bool saved = false;
float savedFOV = 0.0f;
bool MainAddress() {
	Engine = *(uintptr_t*)(ModuleBase + OFFSET_ENGINE);
	if (!IsValid((DWORD64)Engine)) return false;

	Game = (UEngine*)(Engine);
	if (!IsValid((DWORD64)Game)) return false;

	LocalPlayer = Game->GamePlayers.GetByIndex(0);
	if (!IsValid((DWORD64)LocalPlayer)) return false;

	PlayerController = LocalPlayer->Actor;
	if (!IsValid((DWORD64)PlayerController)) return false;

	ReplicationInfo = PlayerController->PlayerReplicationInfo;
	if (!IsValid((DWORD64)ReplicationInfo)) return false;

	AcknowledgedPawn = PlayerController->AcknowledgedPawn;
	if (!IsValid((DWORD64)AcknowledgedPawn)) return false;

	PlayerCamera = PlayerController->PlayerCamera;
	if (!IsValid((DWORD64)PlayerCamera)) return false;

	WorldInfo = PlayerController->WorldInfo;
	if (!IsValid((DWORD64)WorldInfo)) return false;

	Weapon = AcknowledgedPawn->Weapon;
	if (!IsValid((DWORD64)Weapon)) return false;

	// Real FOV = DefaultFOV * FOVMultiplier
	FOV = PlayerController->PlayerCamera->DefaultFOV * PlayerController->LODDistanceFactor;

	if (!FOV || FOV == 0)
		return false;

	if (!saved)
	{
		savedFOV = PlayerController->PlayerCamera->DefaultFOV;
		saved = !saved;
	}

	if (Settings.FOV)
		PlayerController->PlayerCamera->DefaultFOV = Settings.FOVValue;
	else
		PlayerController->PlayerCamera->DefaultFOV = savedFOV;

	return true;
}


float speed = 7000.0f;
FVector newVector = { 0, 0, 0 };
void doAimbot()
{
	if (LockedPawn->Health > 1)
	{
		FRotator AimRotation = FRotator{ 0, 0, 0 };

		float lastRenderTime = LockedPawn->Mesh->LastRenderTime;
		float timeSeconds = WorldInfo->TimeSeconds;
		bool isPawnVisible = (lastRenderTime > timeSeconds - 0.05f);

		if (isPawnVisible)
		{
			if (Settings.AimbotPrediction)
			{
				if (Weapon->m_FiredProjectiles.Num() > 0)
				{
					speed = Weapon->m_FiredProjectiles.GetByIndex(0)->Speed;
				}

				FVector TargetVelocity = LockedPawn->Velocity;
				FVector TargetLocation = LockedPawn->Location;
				float TravelTime = maths::GetDistance(AcknowledgedPawn->Location, TargetLocation) / speed;

				FVector PredictedTargetLocation = {
					(TargetLocation.X + TargetVelocity.X * TravelTime),
					(TargetLocation.Y + TargetVelocity.Y * TravelTime),
					 TargetLocation.Z
				};

				maths::AimAtVector(PredictedTargetLocation, PlayerCamera->RealLocation, AimRotation);
				PlayerController->Rotation = AimRotation;
			}
			else
			{
				if (!Settings.AimbotSmoothing)
				{
					maths::AimAtVector(LockedHead, PlayerCamera->RealLocation, AimRotation);
					PlayerController->Rotation = AimRotation;
				}
			}
		}
	}
	else
	{
		Locked = false;
		LockedPawn = nullptr;
		return;
	}
}

void doActorsLoop()
{
	if (Settings.ESP.Players)
	{
		if (!IsValid((DWORD64)WorldInfo)) return;
		if (!IsValid((DWORD64)AcknowledgedPawn)) return;
		if (!IsValid((DWORD64)PlayerController)) return;
		if (!IsValid((DWORD64)PlayerCamera)) return;
		if (!IsValid((DWORD64)PlayerController->PlayerReplicationInfo->Team)) return;

		APawn* CurrentPawn = WorldInfo->PawnList;

		while (IsValid((DWORD64)CurrentPawn))
		{
			if (!CurrentPawn || CurrentPawn == nullptr || !IsValid((DWORD64)CurrentPawn))
			{
				CurrentPawn = CurrentPawn->NextPawn;
				continue;
			}

			if (!IsValid((DWORD64)CurrentPawn->PlayerReplicationInfo) || !CurrentPawn->PlayerReplicationInfo || CurrentPawn->PlayerReplicationInfo == nullptr || !IsValid((DWORD64)CurrentPawn->PlayerReplicationInfo->Team) || !CurrentPawn->PlayerReplicationInfo->Team || CurrentPawn->PlayerReplicationInfo->Team == nullptr)
			{
				CurrentPawn = CurrentPawn->NextPawn;
				continue;
			}

			if (CurrentPawn->PlayerReplicationInfo->Team->TeamIndex == PlayerController->PlayerReplicationInfo->Team->TeamIndex ||
				!CurrentPawn->PlayerReplicationInfo->PlayerName.IsValid() ||
				CurrentPawn == AcknowledgedPawn ||
				CurrentPawn->Health < 1)
			{
				CurrentPawn = CurrentPawn->NextPawn;
				continue;
			}

			FBoxSphereBounds PlayerHitbox = CurrentPawn->Mesh->Bounds;
			FString PlayerName = CurrentPawn->PlayerReplicationInfo->PlayerName;

			FVector min, max, posFeet;
			ImVec2 smin, smax, pos;

			min = maths::VectorSubtract(PlayerHitbox.Origin, PlayerHitbox.BoxExtent);
			max = maths::VectorAdd(PlayerHitbox.Origin, PlayerHitbox.BoxExtent);

			posFeet.X = CurrentPawn->Location.X;
			posFeet.Y = CurrentPawn->Location.Y;
			posFeet.Z = CurrentPawn->Location.Z - CurrentPawn->BaseEyeHeight;

			if (W2S(min, smin, PlayerController->Rotation, PlayerCamera->RealLocation, FOV) &&
				W2S(max, smax, PlayerController->Rotation, PlayerCamera->RealLocation, FOV) &&
				W2S(posFeet, pos, PlayerController->Rotation, PlayerCamera->RealLocation, FOV))
			{
				float flWidth = fabs((smax.y - smin.y) / 4);
				float healthPercentage = CurrentPawn->Health / CurrentPawn->r_fCachedMaxHealth;

				float lastRenderTime = CurrentPawn->Mesh->LastRenderTime;
				float timeSeconds = WorldInfo->TimeSeconds;
				bool isPawnVisible = (lastRenderTime > timeSeconds - 0.05f);

				ImU32 ESPColor = Colors::WhiteCl;
				if (isPawnVisible)
					ESPColor = Colors::RedCL;
				else
					ESPColor = Colors::WhiteCl;

				if (Settings.ESP.Name)
				{
					char PlayerNameBuf[64];
					if (CurrentPawn->PlayerReplicationInfo->PlayerName.IsValid())
					{
						sprintf_s(PlayerNameBuf, E("%ws | %.1f%%"), PlayerName.c_str(), healthPercentage*100);
						ImGui::GetOverlayDrawList()->AddText(ImVec2(pos.x - flWidth, smax.y - 20), Colors::LimeCL, PlayerNameBuf);
					}
				}

				if (Settings.ESP.Tracer)
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2, height), ImVec2(pos.x, smin.y), ESPColor);

				if (Settings.ESP.Health)
				{
					ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(pos.x - flWidth, smax.y - 5), ImVec2(pos.x + flWidth + 2, smax.y), Colors::BlackCL); // Health background
					ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(pos.x - flWidth, smax.y - 5), ImVec2((pos.x - flWidth) + ((flWidth * 2) * healthPercentage), smax.y), Colors::LimeCL); // Health
				}

				if (Settings.ESP.Box)
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x - flWidth, smin.y), ImVec2(pos.x + flWidth, smin.y), ESPColor); // bottom
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x - flWidth, smax.y), ImVec2(pos.x + flWidth, smax.y), ESPColor); // up
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x - flWidth, smin.y), ImVec2(pos.x - flWidth, smax.y), ESPColor); // left
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(pos.x + flWidth, smin.y), ImVec2(pos.x + flWidth, smax.y), ESPColor); // right
				}
			}
			CurrentPawn = CurrentPawn->NextPawn;
			continue;
		}
	}

	if (Settings.Aimbot && GetAimKey())
	{
		if (!IsValid((DWORD64)WorldInfo)) return;

		APawn* CurrentPawn = WorldInfo->PawnList;

		while (IsValid((DWORD64)CurrentPawn))
		{
			if (IsValid((DWORD64)CurrentPawn->PlayerReplicationInfo) && IsValid((DWORD64)CurrentPawn->PlayerReplicationInfo->Team))
			{
				float ClosestDistance = 999999.0f;

				int LocalTeam = ReplicationInfo->Team->TeamIndex;
				int EnemyTeam = CurrentPawn->PlayerReplicationInfo->Team->TeamIndex;

				if (!CurrentPawn->PlayerReplicationInfo->PlayerName.IsValid() ||
					CurrentPawn == AcknowledgedPawn ||
					LocalTeam == EnemyTeam ||
					CurrentPawn->Health < 1)
				{
					CurrentPawn = CurrentPawn->NextPawn;
					continue;
				}

				FVector head;
				ImVec2 headPos;

				head.X = CurrentPawn->Location.X;
				head.Y = CurrentPawn->Location.Y;
				head.Z = CurrentPawn->Location.Z - bones[Settings.AimPos] + CurrentPawn->BaseEyeHeight;

				if (LockedPawn != nullptr)
				{
					LockedHead.X = LockedPawn->Location.X;
					LockedHead.Y = LockedPawn->Location.Y;
					LockedHead.Z = LockedPawn->Location.Z - bones[Settings.AimPos] + LockedPawn->BaseEyeHeight;
				}

				if (Locked && LockedPawn && IsValid((DWORD64)LockedPawn))
				{
					doAimbot();
					CurrentPawn = CurrentPawn->NextPawn;
					continue;
				}
				else if (!Locked)
				{
					if (W2S(head, headPos, PlayerController->Rotation, PlayerCamera->RealLocation, FOV))
					{
						float aimfov = (Settings.AimbotFOV + 1) * ((PlayerController->LODDistanceFactor * 4));
						float ScreenCX = width / 2;
						float ScreenCY = height / 2;
						float cx = headPos.x;
						float cy = headPos.y;
						float radiusx_ = aimfov * (ScreenCX / FOV);
						float radiusy_ = aimfov * (ScreenCY / FOV);
						float crosshairDistance = maths::GetCrosshairDistance(cx, cy, ScreenCX, ScreenCY);

						if (cx >= ScreenCX - radiusx_ && cx <= ScreenCX + radiusx_ && cy >= ScreenCY - radiusy_ && cy <= ScreenCY + radiusy_)
						{
							if (crosshairDistance < ClosestDistance)
							{
								ClosestDistance = crosshairDistance;
								LockedPawn = CurrentPawn;
							}

							if (!Locked && LockedPawn && IsValid((DWORD64)LockedPawn))
							{
								Locked = true;
								doAimbot();
							}
							else
							{
								LockedPawn = nullptr;
								LockedHead = FVector{ 0, 0, 0 };
								Locked = false;
								CurrentPawn = CurrentPawn->NextPawn;
								continue;
							}
						}
						CurrentPawn = CurrentPawn->NextPawn;
						continue;
					}
				}
				CurrentPawn = CurrentPawn->NextPawn;
				continue;
			}
			CurrentPawn = CurrentPawn->NextPawn;
			continue;
		}
	}
	else
	{
		LockedPawn = nullptr;
		LockedHead = FVector{ 0, 0, 0 };
		Locked = false;
	}
}