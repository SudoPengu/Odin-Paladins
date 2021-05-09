#pragma once

/*

UE3 Signatures

UEngine: 48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 48 39 B9 ? ? ? ?
ProcessEvent: E8 ?? ?? ?? ?? 8D 4E FD
GObject: 48 8B 05 ? ? ? ? 4C 8B 04 0A 4C 33 04 F0 44
GNames: 48 8B 05 ? ? ? ? B9 ? ? ? ? 48 8B 0C 0A 48 BA

*/

#define OFFSET_ENGINE 0x3695B70
#define OFFSET_TLSINDEX 0x4187264
#define OFFSET_GLOBALOBJECTS 0x368063C
#define OFFSET_GLOBALNAMES 0x36805CC
#define OFFSET_PROCESSEVENT 0x17EA30