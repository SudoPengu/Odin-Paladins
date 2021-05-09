#pragma once
#include <cstdint>

// ScriptStruct Core.Object.Rotator
// 0x000C
struct FRotator
{
	int                                                Pitch;                                                    // 0x0000(0x0004) (Edit)
	int                                                Yaw;                                                      // 0x0004(0x0004) (Edit)
	int                                                Roll;                                                     // 0x0008(0x0004) (Edit)
};

// ScriptStruct Core.Object.Vector
// 0x000C
struct FVector
{
	float                                              X;                                                        // 0x0000(0x0004) (Edit)
	float                                              Y;                                                        // 0x0004(0x0004) (Edit)
	float                                              Z;                                                        // 0x0008(0x0004) (Edit)
};

// ScriptStruct Core.Object.Vector2D
// 0x0008
struct FVector2D
{
	float                                              X;                                                        // 0x0000(0x0004) (Edit)
	float                                              Y;                                                        // 0x0004(0x0004) (Edit)
};

// ScriptStruct Core.Object.Color
// 0x0004
struct FColor
{
	unsigned char                                      B;                                                        // 0x0000(0x0001) (Edit)
	unsigned char                                      G;                                                        // 0x0001(0x0001) (Edit)
	unsigned char                                      R;                                                        // 0x0002(0x0001) (Edit)
	unsigned char                                      A;                                                        // 0x0003(0x0001) (Edit)

	inline FColor()
		: R(0), G(0), B(0), A(0)
	{ }

	inline FColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: R(r),
		G(g),
		B(b),
		A(a)
	{ }

};

// ScriptStruct Core.Object.Quat
// 0x0010
struct FQuat
{
	float                                              X;                                                        // 0x0000(0x0004) (Edit)
	float                                              Y;                                                        // 0x0004(0x0004) (Edit)
	float                                              Z;                                                        // 0x0008(0x0004) (Edit)
	float                                              W;                                                        // 0x000C(0x0004) (Edit)
};

// ScriptStruct Core.Object.BoxSphereBounds
// 0x001C
struct FBoxSphereBounds
{
	struct FVector                                     Origin;                                                   // 0x0000(0x000C) (Edit)
	struct FVector                                     BoxExtent;                                                // 0x000C(0x000C) (Edit)
	float                                              SphereRadius;                                             // 0x0018(0x0004) (Edit)
};

// ScriptStruct Core.Object.BoneAtom
// 0x0020
struct FBoneAtom
{
	struct FQuat                                       Rotation;                                                 // 0x0000(0x0010)
	struct FVector                                     Translation;                                              // 0x0010(0x000C)
	float                                              Scale;                                                    // 0x001C(0x0004)
};

// ScriptStruct Core.Object.Box
// 0x0019
struct FBox
{
	struct FVector                                     Min;                                                      // 0x0000(0x000C) (Edit)
	struct FVector                                     Max;                                                      // 0x000C(0x000C) (Edit)
	unsigned char                                      IsValid;                                                  // 0x0018(0x0001)
};