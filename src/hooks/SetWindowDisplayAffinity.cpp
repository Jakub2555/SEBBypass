#include "Hooks.h"

/*
*   Doesnt allow to set WDA_EXCLUDEFROMCAPTURE flag to SEB windows. Allowing capture of their windows.
*/
BOOL __stdcall hooks::HkSetWindowDisplayAffinity(HWND window, DWORD affinity)
{
    if (affinity == 0x00000011) // WDA_EXCLUDEFROMCAPTURE
        return oSetWindowDisplayAffinity(window, 0x00000000);

    return oSetWindowDisplayAffinity(window, affinity);
}