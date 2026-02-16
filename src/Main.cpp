#include <Windows.h>

#include <Hooks.h>
#include "Notepad.h"

void Main()
{   
    hooks::Initialize();

    notepad::Launch();

    while (true)
    {
        if ((GetAsyncKeyState('K') & 0x0001) && (GetAsyncKeyState(VK_CONTROL) & 0x8000)) // Exit with CTRL + K
            break;
    }

    hooks::Restore();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID reserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main), nullptr, 0, 0));
    }

    return TRUE;
}