#include "ccpch.h"
#include "Protection/ThreadAddrSpoof.h"
#include "Core/utils.h"
#include "Core/DummyThread.h"


int32_t __stdcall DllMain(HMODULE hMod, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hMod);
			BypassRiotEAC();
			SpoofThreadLocation(CreateConsole, hMod);
			SpoofThreadLocation(DummyThread, hMod);
			break;
		case DLL_PROCESS_DETACH:
			break;

		default:
			return true;
	}
	return TRUE;
}