#include "Hooks.h"

LRESULT CALLBACK WindowsHookProxy(int code, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

/*
*   Stop SEB from capturing keyboard and mouse inputs.
*/
HHOOK __stdcall hooks::HkSetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
    if (dwThreadId == 0 && hmod != NULL)
    {
        if (idHook == 14) // WH_MOUSE_LL
        {
            return oSetWindowsHookExA(idHook, WindowsHookProxy, hmod, dwThreadId);
        }
        else if (idHook == 13) // WH_KEYBOARD_LL
        {
            return oSetWindowsHookExA(idHook, WindowsHookProxy, hmod, dwThreadId);
        }
    }

    return oSetWindowsHookExA(idHook, lpfn, hmod, dwThreadId);
}