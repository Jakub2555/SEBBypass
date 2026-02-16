#include "Notepad.h"

#include <Windows.h>
#include <TlHelp32.h>

typedef BOOL(__stdcall* SetWindowDisplayAffinity_f)(HWND hWnd, DWORD dwAffinity);
typedef VOID(__stdcall* Sleep_f)(DWORD millies);

struct Data_t
{
    HWND hwnd;
    SetWindowDisplayAffinity_f SetAffinity;
    Sleep_f SleepFunc;
};

/*
*   Function that is being injected and ran inside notepad.
*/

#pragma optimize("", off)

__declspec(noinline)
void __stdcall Shellcode(Data_t* data)
{
    while (true)
    {
        // Set Window of Notepad to be excluded from capture.
        data->SetAffinity(data->hwnd, WDA_EXCLUDEFROMCAPTURE);
        data->SleepFunc(1);
    }
}

#pragma optimize("", on)

/*
*   Launch Notepad and hide it from capture.
*/
bool notepad::Launch()
{
    STARTUPINFOA si;
    memset(&si, 0, sizeof(si));

    si.cb = sizeof(si);

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));

    // Launch Notepad process.
    BOOL status = CreateProcessA("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    if (!status)
        return false;

    // Get Window of Notepad
    HWND hwnd = FindWindowA("Notepad", nullptr);

    // Basic Shellcode Injection code.
    Data_t data = { };
    data.hwnd = hwnd;
    data.SetAffinity = SetWindowDisplayAffinity;
    data.SleepFunc = Sleep;

    BYTE* paramsBase = reinterpret_cast<BYTE*>(VirtualAllocEx(pi.hProcess, nullptr, sizeof(Data_t), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
    if (paramsBase == nullptr)
        return false;

    WriteProcessMemory(pi.hProcess, paramsBase, &data, sizeof(Data_t), nullptr);

    BYTE* shellcodeBase = reinterpret_cast<BYTE*>(VirtualAllocEx(pi.hProcess, nullptr, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
    if (shellcodeBase == nullptr)
        return false;

    WriteProcessMemory(pi.hProcess, shellcodeBase, Shellcode, 0x1000, nullptr);

    CloseHandle(CreateRemoteThread(pi.hProcess, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(shellcodeBase), paramsBase, 0, nullptr));

    Sleep(200);

    // Cleanup
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    memset(&pi, 0, sizeof(pi));
    memset(&si, 0, sizeof(si));
}