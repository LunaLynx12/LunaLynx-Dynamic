#pragma once
#include "ccpch.h"

void* NtdllAddress = GetProcAddress(GetModuleHandleA(xorstr_("ntdll.dll")), xorstr_("RtlInterlockedCompareExchange64"));
void* KernelAddress = GetProcAddress(GetModuleHandleA(xorstr_("kernel.dll")), xorstr_("GetSystemLeapSecondInformation"));

DWORD ntdll170 = (DWORD)NtdllAddress + 0x170;
DWORD KernelEC85 = (DWORD)KernelAddress + 0xEC85;

void GetModuleBaseAddr()
{
	// Get module base

	DWORD ModuleBaseAddr;

	__asm __volatile
	{
		push esi

		xor esi, esi //nulling esi

		mov esi, FS : [0x30] //get peb

		lea esi,[esi] //peb pointer

		add esi, 0x8 //add 8 bytes to the pointer, which points to the base address

		mov esi,[esi] //deregrnce it

		mov ModuleBaseAddr, esi

		pop esi
	}

	std::cout << "Module Base Address is: " << std::hex << ModuleBaseAddr << std::endl;
}

void __declspec(naked) CopyZwVirtualProtect() // ZwVirtualProtectMemory copy function
{
	__asm
	{
		mov eax, 0x50
		mov edx, ntdll170 // ntdll.RtlInterlockedCompareExchange64 + 170
		call edx
		ret 0x14
	}
}

BOOL __declspec(naked) __cdecl CopyVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) // VirtualProtect 
{
	__asm
	{
		mov edi, edi
		push ebp
		mov ebp, esp
		push ecx
		push ecx
		mov eax, [ebp + 0xC]
		push esi
		push[ebp + 0x14]
		mov[ebp - 4], eax
		push[ebp + 0x10]
		mov eax, [ebp + 8]
		mov[ebp - 8], eax
		lea eax, [ebp - 4]
		push eax
		lea eax, [ebp - 8]
		push eax
		push - 1
		call CopyZwVirtualProtect
		mov esi, eax
		test esi, esi
		js KK //KERNELBASE.GetSystemLeapSecondInformation + EC85 hack
		xor eax, eax
		inc eax
		pop esi
		leave
		ret 0x10

		KK:
		jmp KernelEC85
	}
}

void CreateConsole()
{
	

	AllocConsole();
	FILE* fp = nullptr;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	printf("thread works!\n");

	GetModuleBaseAddr();
	

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void BypassRiotEAC()
{
	// CopyVirtualProtect((PVOID*)og_fun, 1, (PAGE_EXECUTE_READ | PAGE_GUARD), &oldProtection);
}