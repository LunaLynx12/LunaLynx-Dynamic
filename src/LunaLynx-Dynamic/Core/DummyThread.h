#pragma once
#include "ccpch.h"
#include "LunaLynx-Dynamic/Protection/UnlinkModule.h"
#include "utils.h"

void DummyThread()
{
	Sleep(3000);

	UnlinkModule("LunaLynx-Dynamic.dll");
}