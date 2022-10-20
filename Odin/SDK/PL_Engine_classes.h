#pragma once

#include <unordered_set>
#include <cstdint>
#include <set>
#include <string>
#include <locale>

#include "Helpers/ProcessEvent.h"

#include "PL_Core_structs.h"

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline size_t Num() const
	{
		return Count;
	};

	inline T& operator[](size_t i)
	{
		return Data[i];
	};

	inline const T& operator[](size_t i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(size_t i) const
	{
		return i < Num();
	}

	inline T& GetByIndex(size_t i)
	{
		return Data[i];
	}

	inline const T& GetByIndex(size_t i) const
	{
		return Data[i];
	}

private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

template<class T>
struct TAntiCheatArray
{
	friend struct FString;
private:
	uintptr_t Decrypt(size_t i) {
		return reinterpret_cast<uintptr_t>(Data[i]);
	}

	T GetData(size_t i) {
		return reinterpret_cast<T>(Decrypt(i));
	}
public:
	TAntiCheatArray()
	{
		Data = nullptr;
		Count = Unk00 = 0;
	};

	size_t Num() const
	{
		return Count;
	};

	T operator[](size_t i)
	{
		return GetData(i);
	};

	T GetByIndex(size_t i)
	{
		return GetData(i);
	}

	bool IsValidIndex(size_t i)
	{
		uintptr_t addr = Decrypt(i);
		if (addr == NULL || IsBadReadPtr((void*)addr, 1))
			return false;
		return i < Num();
	}

private:
	T* Data;
	__int32 Unk00;
	__int32 Count;
};


struct FPointer
{
	uintptr_t Dummy;
};

struct FQWord
{
	int A;
	int B;
};

class FNameEntry
{
	static const auto NAME_WIDE_MASK = 0x1;
	static const auto NAME_INDEX_SHIFT = 1;

public:
	uint64_t Flags; //0x0000
	uint32_t Index; //0x0008
	char pad_000C[8]; //0x000C
	char Text[1024];

	int32_t GetIndex() const
	{
		return Index >> NAME_INDEX_SHIFT;
	}

	bool IsWide() const
	{
		return Index & NAME_WIDE_MASK;
	}

	const char* GetAnsiName() const
	{
		return Text;
	}

	std::string GetName() const
	{
		return Text;
	}
};

struct FName
{
	uint32_t Index;
	uint32_t Number;

	inline bool operator==(const FName& other) const
	{
		return Index == other.Index;
	};
};

struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	}

	FString(const wchar_t* other)
	{
		Max = Count = *other ? std::wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		const auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

class UObject;

class FScriptInterface
{
private:
	UObject* ObjectPointer;
	void* InterfacePointer;

public:
	UObject* GetObject() const
	{
		return ObjectPointer;
	}

	UObject*& GetObjectRef()
	{
		return ObjectPointer;
	}

	void* GetInterface() const
	{
		return ObjectPointer != nullptr ? InterfacePointer : nullptr;
	}
};

template<class InterfaceType>
class TScriptInterface : public FScriptInterface
{
public:
	InterfaceType* operator->() const
	{
		return (InterfaceType*)GetInterface();
	}

	InterfaceType& operator*() const
	{
		return *((InterfaceType*)GetInterface());
	}

	operator bool() const
	{
		return GetInterface() != nullptr;
	}
};

struct FScriptDelegate
{
	unsigned char UnknownData[0x0C];
};

class UClass;
class UFunction;

class UObject //Size: 0x0060
{
public:
	FPointer VfTableObject; // 0x0000
	char pad_0008[0x30]; // 0x0008
	int32_t InternalIndex; //0x0038
	char pad_003C[0x04]; //0x003C
	UObject* Outer; //0x0040
	FName Name; // 0x0048 struct padding might be wrong here | nope :p
	UObject* Class; //0x0050
	UObject* ObjectArcheType; //0x0058

}; // size=0x60

class   UField : public UObject
{
public:
	UField* Next; // 0x0060
}; // size=0x08

class UEnum : public UField
{
public:
	TArray<FName>   Names;
};

class UConst : public UField
{
public:
	FString         Value;
};

class UStruct : public UField //Size: 0x0070 example:  Class Core.Struct // new size: 0x78
{
public:
	char pad_0000[0x10]; //0x0068
	UField* SuperField; //0x0078
	UField* Children; //0x0080
	uint32_t PropertySize; //0x0088
	char pad_0024[0x47]; //0x008C
}; // size=0xD0

class UScriptStruct : public UStruct // example: Class Core.ScriptStruct    
{
public:
	char            UnknownData00[0x24]; // this is probably wrong | nope :p
};

class UFunction : public UStruct
{
public:
	uint32_t FunctionFlags; //0x00D0
	uint16_t iNative; //0x00D4
	uint16_t RepOffset; //0x00D6
	int32_t FName_Index; //0x00D8
	int32_t FName_unknown_data; //0x00DC
	uint16_t NumParams; //0x00E0
	uint16_t ParamSize; //0x00E2
	uint16_t ReturnValueOffset; //0x00E4
	char pad_00E6[0x0A]; //0x00E6
	void* Func; //0x00F0
};

class UState : public UStruct
{
public:
	char pad_0000[0x5C]; // This might be wrong - need to be checked
}; //Size: 0x005C

class UClass : public UStruct
{
public:

	char pad_0000[0x90]; //0x0000
	UObject* ClassDefaultObject; // this is right
	char UnknownData01[0x9C]; // Not sure about this one - need to be checked

	/*
	char            UnknownData00[0x88];
	UObject*        ClassDefaultObject;
	char            UnknownData01[0x70];
	*/
	//char[129];
}; //Size: 0x0204

class UProperty : public UField // Not sure about this one too, might be wrong size
{
public:

	int32_t ArrayDim; //0x0000
	int32_t ElementSize; //0x0004
	FQWord PropertyFlags;
	int32_t Unk; //0x0010
	int32_t Offset; //0x0014
	UProperty* Next;
	int64_t PropertySize;
	char pad_0018[0x08]; //0x0018
}; //Size: 0x0040

class UByteProperty : public UProperty
{
public:
	UEnum* Enum;
};

class UIntProperty : public UProperty
{
public:

};

class UFloatProperty : public UProperty
{
public:

};

class UDoubleProperty : public UProperty
{
public:

};

class UBoolProperty : public UProperty
{
public:
	unsigned long   BitMask;
};

class UObjectProperty : public UProperty
{
public:
	UClass* PropertyClass;
};

class UComponentProperty : public UObjectProperty
{
public:
};

class UClassProperty : public UObjectProperty
{
public:
	UClass* MetaClass;
};

class UInterfaceProperty : public UProperty
{
public:
	UClass* InterfaceClass;
};

class UNameProperty : public UProperty
{
public:
	void* unk;
};

class UStructProperty : public UProperty
{
public:
	UStruct* Struct;
};

class UStrProperty : public UProperty
{
public:

};

class UArrayProperty : public UProperty
{
public:
	UProperty* Inner;
};

class UMapProperty : public UProperty
{
public:
	UProperty* KeyProp;
	UProperty* ValueProp;
};

class UDelegateProperty : public UProperty
{
public:
	UFunction* SignatureFunction;
};

#pragma pack(4)

// Class Engine.Actor
// 0x0220 (0x0280 - 0x0060)
class AActor : public UObject
{
public:
    char                                               pad_0000[0x20];                                           // 0x0060 (0x20)
    struct FVector                                     Location;                                                 // 0x0080(0x000C) (Edit, Const, Net)
    struct FRotator                                    Rotation;                                                 // 0x008C(0x000C) (Edit, Const, Net)
    char                                               pad_0001[0x88];                                           // 0x98 (0x88)
    class AWorldInfo*                                  WorldInfo;                                                // 0x0120(0x0008) (Const, Transient)
    char                                               pad_0002[0x8];                                            // 0x128 (0x8)
    float                                              LastRenderTime;                                           // 0x0130(0x0004) (Transient)
    char                                               pad_0003[0x5c];                                           // 0x134 (0x5c)
    struct FVector                                     Velocity;                                                 // 0x0190(0x000C) (Net)
    struct FVector                                     Acceleration;                                             // 0x019C(0x000C)
    struct FVector                                     AngularVelocity;                                          // 0x01A8(0x000C) (Const, Transient)
    class USkeletalMeshComponent*                      BaseSkelComponent;                                        // 0x01B4(0x0008) (Edit, ExportObject, Component, EditInline)
    struct FName                                       BaseBoneName;                                             // 0x01BC(0x0008) (Edit)
    char                                               pad_0004[0x10];                                           // 0x1c4 (0x10)
    struct FVector                                     RelativeLocation;                                         // 0x01D4(0x000C) (Const, Net)
    struct FRotator                                    RelativeRotation;                                         // 0x01E0(0x000C) (Const, Net)
    char                                               pad_0005[0x68];                                           // 0x1ec (0x68)
    struct FVector                                     LocationPrev;                                             // 0x0254(0x000C)
};

// Class Engine.WorldInfo
// 0x0734 (0x09C8 - 0x0294)
class AWorldInfo
{
public:
    char                                               pad_0000[0x4cc];                                          // 0x0 (0x4cc)
    TArray<class ULevelStreaming*>                     StreamingLevels;                                          // 0x04CC(0x0010) (Edit, Const, EditConst, NeedCtorLink, EditInline)
    char                                               pad_0001[0x10];                                           // 0x4dc (0x10)
    float                                              TimeSeconds;                                              // 0x04EC(0x0004) (Transient)
    char                                               pad_0002[0x60];                                           // 0x4f0 (0x60)
    struct FString                                     ComputerName;                                             // 0x0550(0x0010) (NeedCtorLink)
    struct FString                                     EngineVersion;                                            // 0x0560(0x0010) (NeedCtorLink)
    char                                               pad_0003[0x10];                                           // 0x570 (0x10)
    class AGameInfo*                                   Game;                                                     // 0x0580(0x0008)
    char                                               pad_0004[0x4];                                            // 0x588 (0x4)
    float                                              WorldGravityZ;                                            // 0x058C(0x0004) (Net, Transient)
    float                                              DefaultGravityZ;                                          // 0x0590(0x0004) (Const, Config, GlobalConfig)
    float                                              GlobalGravityZ;                                           // 0x0594(0x0004) (Edit)
    char                                               pad_0005[0x14];                                           // 0x598 (0x14)
    class AController*                                 ControllerList;                                           // 0x05AC(0x0008) (Const)
    class APawn*                                       PawnList;                                                 // 0x05B4(0x0008) (Const)
};

// Class Engine.Engine
// 0x083C (0x08A4 - 0x0068)
class UEngine
{
public:
    char                                               pad_0000[0x6d8];                                          // 0x0 (0x6d8)
    TArray<class ULocalPlayer*>                        GamePlayers;                                              // 0x06D8(0x0010) (AlwaysInit, NeedCtorLink)
};

// Class Engine.Player
// 0x002C (0x008C - 0x0060)
class UPlayer
{
public:
    char                                               pad_0000[0x68];                                           // 0x0 (0x68)
    class APlayerController*                           Actor;                                                    // 0x0068(0x0008) (Const, Transient)
};

// Class Engine.LocalPlayer
// 0x03E0 (0x046C - 0x008C)
class ULocalPlayer : public UPlayer
{
public:
    char                                               pad_0000[0x24];                                           // 0x0070(0x0024)
    int                                                ControllerId;                                             // 0x0094(0x0004)
    char                                               pad_0001[0x54];                                           // 0x98 (0x54)
    struct FVector                                     LastViewLocation;                                         // 0x00EC(0x000C) (Transient)
    char                                               pad_0002[0x334];                                          // 0xf8 (0x334)
    struct FString                                     LastMap;                                                  // 0x042C(0x0010) (NeedCtorLink)
    char                                               pad_0003[0x18];                                           // 0x43c (0x18)
    float                                              ServerAuthTimestamp;                                      // 0x0454(0x0004)
    int                                                ServerAuthTimeout;                                        // 0x0458(0x0004)
    int                                                ServerAuthRetryCount;                                     // 0x045C(0x0004)
    int                                                MaxServerAuthRetryCount;                                  // 0x0460(0x0004)
};

// Class Engine.Controller
// 0x01F0 (0x0470 - 0x0280)
class AController : public AActor
{
public:
    char                                               pad_0000[0x28];                                           // 0x0260(0x0028)
    class APawn*                                       Pawn;                                                     // 0x0288(0x0008) (Net, EditInline)
    class APlayerReplicationInfo*                      PlayerReplicationInfo;                                    // 0x0290(0x0008) (Net, EditInline)
    int                                                PlayerNum;                                                // 0x0298(0x0004) (Const)
    class AController*                                 NextController;                                           // 0x029C(0x0008) (Const)

	bool IsDead();
};

// Class Engine.PlayerController
// 0x02FC (0x076C - 0x0470)
class APlayerController : public AController
{
public:
    char                                               pad_0000[0x1CC];                                          // 0x02A4(0x01CC)
    class UPlayer*                                     Player;                                                   // 0x0470(0x0008) (Const)
    class ACamera*                                     PlayerCamera;                                             // 0x0478(0x0008) (Edit, EditInline)
    char                                               pad_0001[0x18];                                           // 0x480 (0x18)
    class APawn*                                       AcknowledgedPawn;                                         // 0x0498(0x0008)
    char                                               pad_0002[0x28];                                           // 0x4a0 (0x28)
    float                                              DefaultFOV;                                               // 0x04C8(0x0004)
    float                                              LODDistanceFactor;                                        // 0x04CC(0x0004) (Const)
};

// Class Engine.Camera
// 0x0384 (0x0604 - 0x0280)
class ACamera : public AActor
{
public:
    char                                               pad_0000[0x20];                                           // 0x0260(0x0020)
    class APlayerController*                           PCOwner;                                                  // 0x0280(0x0008)
    struct FName                                       CameraStyle;                                              // 0x0288(0x0008)
    float                                              DefaultFOV;                                               // 0x0290(0x0004)
    char                                               pad_0001[0x200];                                          // 0x0294(0x2000)
    struct FVector                                     RealLocation;                                             // 0x0494(0x000C)
    char                                               pad_0002[0x34];                                           // 0x04A0(0x0034)
    struct FVector                                     Location;                                                 // 0x04C8(0x000C)
};

// Class Engine.PrimitiveComponent
// 0x01C7 (0x024C - 0x0085)
class UPrimitiveComponent : public UObject
{
public:
    char                                               pad_0000[0x40];                                           // 0x0060(0x0040)
    struct FBoxSphereBounds                            Bounds;                                                   // 0x00A0(0x001C) (Const, Native, Transient)
    char                                               pad_0001[0xe8];                                           // 0x00bc(0x00e8)
    int                                                VisibilityId;                                             // 0x01A4(0x0004) (DuplicateTransient)
    char                                               pad_0002[0x58];                                           // 0x01a8(0x0058)
    struct FVector                                     Translation;                                              // 0x0200(0x000C) (Edit, Const)
    struct FRotator                                    Rotation;                                                 // 0x020C(0x000C) (Edit, Const)
    float                                              Scale;                                                    // 0x0218(0x0004) (Edit, Const)
    struct FVector                                     Scale3D;                                                  // 0x021C(0x000C) (Edit, Const)
    float                                              BoundsScale;                                              // 0x0228(0x0004) (Edit, Const)
    char                                               pad_0003[0x14];                                           // 0x022c(0x0014)
    float                                              LastSubmitTime;                                           // 0x0240(0x0004) (Const, Transient)
    float                                              LastRenderTime;                                           // 0x0244(0x0004) (Transient)
};

// Class Engine.SkeletalMeshComponent
// 0x0520 (0x07B4 - 0x0294)
class USkeletalMeshComponent : public UPrimitiveComponent
{
public:
    char                                               pad_0000[0x4C];                                           // 0x0248(0x004C)
    class USkeletalMesh*                               SkeletalMesh;                                             // 0x0294(0x0008) (Edit)
    class USkeletalMeshComponent*                      AttachedToSkelComponent;                                  // 0x029C(0x0008) (ExportObject, Component, EditInline)
    char                                               pad_0001[0xb0];                                           // 0x2a4 (0xb0)
    TArray<struct FBoneAtom>                           LocalAtoms;                                               // 0x0354(0x0010) (Const, Native, Transient)
};

// ScriptStruct TgGame.TgDevice.AccuracySettings
// 0x001C
struct FAccuracySettings
{
    int                                                bUsesAdvancedAccuracy;                                    // 0x0000(0x0004)
    float                                              fMaxAccuracy;                                             // 0x0004(0x0004)
    float                                              fMinAccuracy;                                             // 0x0008(0x0004)
    float                                              fAccuracyLossPerShot;                                     // 0x000C(0x0004)
    float                                              fAccuracyGainPerSec;                                      // 0x0010(0x0004)
    float                                              fAccuracyGainDelay;                                       // 0x0014(0x0004)
    int                                                nNumFreeShots;                                            // 0x0018(0x0004)
};

// ScriptStruct TgGame.TgDevice.RecoilSettings
// 0x0010
struct FRecoilSettings
{
    int                                                bUsesRecoil;                                              // 0x0000(0x0004)
    float                                              fRecoilReductionPerSec;                                   // 0x0004(0x0004)
    float                                              fRecoilCenterDelay;                                       // 0x0008(0x0004)
    float                                              fRecoilSmoothRate;                                        // 0x000C(0x0004)
};

// Class Engine.Projectile
// 0x005C (0x02DC - 0x0280)
class AProjectile : public AActor
{
public:
	char                                               pad_0000[0x20];                                           // 0x0260(0x0020)
	float                                              Speed;                                                    // 0x0280(0x0004) (Edit, Net)
	float                                              MaxSpeed;                                                 // 0x0284(0x0004) (Edit, Net)
};

// Class TgGame.TgProjectile
// 0x0170 (0x044C - 0x02DC)
class ATgProjectile : public AProjectile
{
public:
	char                                               pad_0000[0x78];                                           // 0x028C(0x0078)
	int                                                r_nProjectileId;                                          // 0x0304(0x0004) (Net)
	float                                              r_fDuration;                                              // 0x0308(0x0004) (Net)
	char                                               pad_0001[0x30];                                           // 0x30c (0x30)
	float                                              r_fAccelRate;                                             // 0x033C(0x0004) (Net)
};

// Class TgGame.TgDevice
// 0x0710 (0x0A0C - 0x02FC)
class ATgDevice : public AActor
{
public:
	char                                               pad_0000[0x248];                                          // 0x260 (0x248)
	int                                                r_nAmmoClipCount;                                         // 0x04A8(0x0004) (Net)
	char                                               pad_0001[0x168];                                          // 0x4ac (0x168)
	TArray<class ATgProjectile*>                       m_FiredProjectiles;                                       // 0x0614(0x0010) (NeedCtorLink)
	float                                              m_fForce3PPersistDuration;                                // 0x0624(0x0004)
	float                                              m_fForce3PPersistTimer;                                   // 0x0628(0x0004)
	char                                               pad_0002[0x29c];                                          // 0x62c (0x29c)
	struct FAccuracySettings                           m_AccuracySettings;                                       // 0x08C8(0x001C) (Edit)
	char                                               pad_0003[0x70];                                           // 0x8e4 (0x70)
	float                                              m_fCurrentAdvancedAccuracy;                               // 0x0954(0x0004)
	float                                              m_fLastShotTimestamp;                                     // 0x0958(0x0004)
	int                                                m_nFreeShotsLeft;                                         // 0x095C(0x0004)
	float                                              m_fLastMinAccuracy;                                       // 0x0960(0x0004)
	char                                               pad_0004[0x4];                                            // 0x964 (0x4)
	struct FRecoilSettings                             m_RecoilSettings;                                         // 0x0968(0x0010) (Edit)
	char                                               pad_0005[0x44];                                           // 0x978 (0x44)
	float                                              m_fStartFiringTimestamp;                                  // 0x09BC(0x0004)
	float                                              m_fEndFiringTimeStamp;                                    // 0x09C0(0x0004)
	float                                              m_fAccumulatedFiringTime;                                 // 0x09C4(0x0004)
	int                                                m_nRandRecoilNum;                                         // 0x09C8(0x0004) (Transient)
	int                                                r_nRecoilSeed;                                            // 0x09CC(0x0004) (Net, Transient)

	bool IsFiring();
};

// Class Engine.Pawn
// 0x0328 (0x05A8 - 0x0280)
class APawn : public AActor
{
public:
    char                                               pad_0000[0x44];                                           // 0x0260(0x0044)
    class AController*                                 Controller;                                               // 0x02A4(0x0008) (Net, EditInline)
    class APawn*                                       NextPawn;                                                 // 0x02AC(0x0008) (Const)
    char                                               pad_0001[0x38];                                           // 0x2b4 (0x38)
    int                                                FullHeight;                                               // 0x02EC(0x0004) (Const)
    char                                               pad_0002[0xb4];                                           // 0x2f0 (0xb4)
    float                                              BaseEyeHeight;                                            // 0x03A4(0x0004) (Edit)
    float                                              EyeHeight;                                                // 0x03A8(0x0004) (Edit)
    char                                               pad_0003[0x18];                                           // 0x3ac (0x18)
    int                                                Health;                                                   // 0x03C4(0x0004) (Edit, Net)
    int                                                HealthMax;                                                // 0x03C8(0x0004) (Edit, Net)
    char                                               pad_0004[0x74];                                           // 0x03CC(0x0074)
    class APlayerReplicationInfo*                      PlayerReplicationInfo;                                    // 0x0440(0x0008) (Net, EditInline)
    char                                               pad_0005[0x44];                                           // 0x0448(0x0044)
    class USkeletalMeshComponent*                      Mesh;                                                     // 0x048C(0x0008) (Edit, ExportObject, Component, EditInline)
    char                                               pad_0006[0x50];                                           // 0x494 (0x50)
    class ATgDevice*                                   Weapon;                                                   // 0x04E4(0x0008)
    char                                               pad_0007[0x10b];                                          // 0x4ec (0x10c)
	int                                                r_ReplicatedDeviceState;									 // 0x05F7(0x0004) (Net)
	char                                               pad_0008[0x7c];                                           // 0x05FC(0x0078)
	unsigned long                                      r_bIsWallHacking;                                         // 0x0678(0x0004) (Net)
	char                                               pad_0009[0xac8];                                          // 0x0678(0x0a94)
	float                                              r_fCachedMaxHealth;                                       // 0x110C(0x0004) (Net)
};

// Class Engine.PlayerReplicationInfo
// 0x0200 (0x0480 - 0x0280)
class APlayerReplicationInfo
{
public:
    char                                               pad_0000[0x290];                                          // 0x0 (0x290)
    struct FString                                     PlayerName;                                               // 0x0290(0x0010) (Net, NeedCtorLink)
    char                                               pad_0001[0x10];                                           // 0x02A0 (0x10)
    int                                                PlayerID;                                                 // 0x02B0(0x0004) (Net)
    char                                               pad_0002[0x228];                                          // 0x2b4 (0x228)
    class ATeamInfo*                                   Team;                                                     // 0x04DC(0x0008) (Net, EditInline)
};

// Class Engine.TeamInfo
// 0x0020 (0x02A0 - 0x0280)
class ATeamInfo
{
public:
    char                                               pad_0000[0x280];                                          // 0x0 (0x280)
    struct FString                                     TeamName;                                                 // 0x0280(0x0010) (Const, Net, Localized, NeedCtorLink)
    char                                               pad_0001[0x8];                                            // 0x290 (0x8)
    int                                                TeamIndex;                                                // 0x0298(0x0004) (Net)
};