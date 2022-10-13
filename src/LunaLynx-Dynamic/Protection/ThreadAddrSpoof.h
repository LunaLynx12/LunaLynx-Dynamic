#pragma once
#include "ccpch.h"

using _RtlCreateUserThread = NTSTATUS(NTAPI*)(HANDLE ProcessHandle,
	PSECURITY_DESCRIPTOR SecurityDescriptor,
	BOOLEAN CreateSuspended,
	ULONG StackZeroBits,
	SIZE_T StackReserve,
	SIZE_T StackCommit,
	void* StartAddress,
	void* Parameter,
	PHANDLE ThreadHandle,
	void* ClientId
	);

void* SpoofThreadLocation(void* thread, HMODULE& hModule);
