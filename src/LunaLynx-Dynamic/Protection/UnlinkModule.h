#pragma once
#include "LunaLynx-Dynamic/WinInternals/Peb.h"

void ClearListEntries(int EntryOffset, const char* ModName);

void UnlinkModule(const char* TargetModName);