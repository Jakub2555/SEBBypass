#include "Hooks.h"

#include <minhook/MinHook.h>

bool hooks::Initialize()
{
    if (MH_Initialize() != MH_OK)
        return false;

    if (MH_CreateHookApi(L"user32.dll", "CallNextHookEx", &HkCallNextHookEx, reinterpret_cast<LPVOID*>(&oCallNextHookEx)) != MH_OK)
        return false;

    if (MH_CreateHookApi(L"user32.dll", "SetWinEventHook", &HkSetWinEventHook, reinterpret_cast<LPVOID*>(&oSetWinEventHook)) != MH_OK)
        return false;

    if (MH_CreateHookApi(L"ntdll.dll", "NtQuerySystemInformation", &HkNtQuerySystemInformation, reinterpret_cast<LPVOID*>(&oNtQuerySystemInformation)) != MH_OK)
        return false;

    if (MH_CreateHookApi(L"user32.dll", "SetWindowsHookExA", &HkSetWindowsHookExA, reinterpret_cast<LPVOID*>(&oSetWindowsHookExA)) != MH_OK)
        return false;

    if (MH_CreateHookApi(L"user32.dll", "SetWindowDisplayAffinity", &HkSetWindowDisplayAffinity, reinterpret_cast<LPVOID*>(&oSetWindowDisplayAffinity)) != MH_OK)
        return false;

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        return false;

    return true;
}

void hooks::Restore()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}