#include "processtools.h"

//Get Process ID From an executable name using toolhelp32Snapshot
DWORD GetProcID(wchar_t* exeName)
{
	PROCESSENTRY32 procEntry = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!hSnapshot)
	{
		return 0;
	}

	procEntry.dwSize = sizeof(procEntry);

	if (!Process32First(hSnapshot, &procEntry))
	{
		return 0;
	}
    int matchCount = 0;
	do
	{
		// if (!wcscmp(procEntry.szExeFile, exeName))
		// {
		// 	CloseHandle(hSnapshot);
		// 	return procEntry.th32ProcessID;
		// }
		if (wcscmp(procEntry.szExeFile, exeName) == 0)
        {
            matchCount++;
            if (matchCount == 2)
            {
                return procEntry.th32ProcessID;
                break;
            }
        }
	} while (Process32Next(hSnapshot, &procEntry));

	CloseHandle(hSnapshot);
	return 0;
}

//Get ModuleEntry from module name, using toolhelp32snapshot
MODULEENTRY32 GetModule(DWORD dwProcID, wchar_t* moduleName)
{
	MODULEENTRY32 modEntry = { 0 };

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);

	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 curr = { 0 };

		curr.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &curr))
		{
			int matchCount = 0;
			do
			{
				if (!wcscmp(curr.szModule, moduleName))
				{

					matchCount++;
					if (matchCount == 2)
					{
						modEntry = curr;
						break;
					}
				}
			} while (Module32Next(hSnapshot, &curr));
		}
		CloseHandle(hSnapshot);
	}
	return modEntry;
}

//FindDMMAddy
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}
