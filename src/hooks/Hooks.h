#pragma once

#include <Windows.h>
#include <winternl.h>

namespace hooks
{
    bool Initialize();
    void Restore();

    // -------- HOOKS --------

    typedef LRESULT(__stdcall* CallNextHookEx_f)(HHOOK, int, WPARAM, LPARAM);
    inline CallNextHookEx_f oCallNextHookEx = nullptr;
    LRESULT __stdcall HkCallNextHookEx(HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam);

    typedef HWINEVENTHOOK(__stdcall* SetWinEventHook_f)(DWORD, DWORD, HMODULE, WINEVENTPROC, DWORD, DWORD, DWORD);
    inline SetWinEventHook_f oSetWinEventHook = nullptr;
    HWINEVENTHOOK __stdcall HkSetWinEventHook(DWORD eventMin, DWORD eventMax, HMODULE hmodWinEventProc, WINEVENTPROC pfnWinEventProc, DWORD idProcess, DWORD idThread, DWORD dwFlags);

    typedef NTSTATUS(__stdcall* NtQuerySystemInformation_f)(UINT, PVOID, ULONG, PULONG);
    inline NtQuerySystemInformation_f oNtQuerySystemInformation = nullptr;
    NTSTATUS __stdcall HkNtQuerySystemInformation(UINT SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);

    typedef HHOOK(__stdcall* SetWindowsHookExA_f)(int, HOOKPROC, HINSTANCE, DWORD);
    inline SetWindowsHookExA_f oSetWindowsHookExA = nullptr;
    HHOOK __stdcall HkSetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId);

    typedef BOOL(__stdcall* SetWindowDisplayAffinity_f)(HWND, DWORD);
    inline SetWindowDisplayAffinity_f oSetWindowDisplayAffinity = nullptr;
    BOOL __stdcall HkSetWindowDisplayAffinity(HWND window, DWORD affinity);
}