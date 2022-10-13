#include "ccpch.h"
#include "ThreadAddrSpoof.h"

void* SpoofThreadLocation(void* thread, HMODULE& hModule)
{
	uintptr_t fakeadress = rand() & 0xFF;
	int DefaultThreadSize = 1000; // 1mb
	std::srand(std::time(0));

	// Get a random memory address
	for (int i = 1; i < 4; ++i)
	{
		// Store in the lowerst 8 bits of the variable
		fakeadress |= (rand() & 0xFF) << i * 8;
		fakeadress |= (rand() & 0xFF) << i * 8;
		fakeadress |= (rand() & 0xFF) << i * 8;
	}

	while (fakeadress > 0x7FFFFFFF)
		fakeadress -= 0x1000; // if memory is outside of the process address space, sbstract a page until our fake address is within the memory of our process

	while (fakeadress <= 0x0)
		fakeadress += 0x1000;

	VirtualProtect((void*)fakeadress, DefaultThreadSize, PAGE_EXECUTE_READWRITE, NULL);

	FlushInstructionCache(GetCurrentProcess(), (void*)fakeadress, DefaultThreadSize);

	CONTEXT tContext{};

	HANDLE tHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)fakeadress, hModule, CREATE_SUSPENDED, 0);

	if (!tHandle)
		SpoofThreadLocation(thread, hModule); // recursion is it fails

	tContext.ContextFlags = CONTEXT_INTEGER;
	GetThreadContext(tHandle, &tContext);

	tContext.Eax = (ULONG)thread;
	tContext.ContextFlags = CONTEXT_INTEGER;
	SetThreadContext(tHandle, &tContext);

	ResumeThread(tHandle);

	return (void*)tContext.Eax;
}
