#include "Hooks.h"

#include <string>

WINEVENTPROC oCallback = nullptr;
bool found = false;

void __stdcall WinEventCallback(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (hProcess)
    {
        CHAR exeName[MAX_PATH] = { 0 };
        DWORD size = MAX_PATH;
        if (QueryFullProcessImageNameA(hProcess, 0, exeName, &size))
        {
            std::string exePath(exeName);

            if (exePath.find("notepad.exe") != std::string::npos)
            {
                return;
            }
        }

        CloseHandle(hProcess);
    }

    return oCallback(hWinEventHook, event, hwnd, idObject, idChild, idEventThread, dwmsEventTime);
}

/*
*   Hide windows of process we want to hide from Windows event hooks.
*/
HWINEVENTHOOK __stdcall hooks::HkSetWinEventHook(DWORD eventMin, DWORD eventMax, HMODULE hmodWinEventProc, WINEVENTPROC pfnWinEventProc, DWORD idProcess, DWORD idThread, DWORD dwFlags)
{
    if (eventMin == 8U && eventMax == 8U) // EVENT_SYSTEM_CAPTURESTART
    {
        if (oCallback == nullptr)
            oCallback = pfnWinEventProc;

        return oSetWinEventHook(eventMin, eventMax, hmodWinEventProc, WinEventCallback, idProcess, idThread, dwFlags);
    }

    if (eventMin == 3U && eventMax == 3U && !found) // EVENT_SYSTEM_FOREGROUND
    {
        if (oCallback == nullptr)
            oCallback = pfnWinEventProc;

        found = true;
        return oSetWinEventHook(eventMin, eventMax, hmodWinEventProc, WinEventCallback, idProcess, idThread, dwFlags);
    }

    return oSetWinEventHook(eventMin, eventMax, hmodWinEventProc, pfnWinEventProc, idProcess, idThread, dwFlags);
}