#pragma once
#include"memory.hpp"

namespace process
{
	unsigned long get_proc_base(const wchar_t* process_name)
	{
		void* ProcSnap = spoof_return::snap_proc_addr(TH32CS_SNAPPROCESS, 0);
		if (ProcSnap == INVALID_HANDLE_VALUE)
			return -1;

		PROCESSENTRY32W ProcEntry = {};
		ProcEntry.dwSize = sizeof(PROCESSENTRY32);

		if (spoof_return::proc_first_w(ProcSnap, &ProcEntry) == FALSE)
			return -1;

		while (spoof_return::proc_next_w(ProcSnap, &ProcEntry))
		{
			if (!wcscmp(ProcEntry.szExeFile, process_name)) {
				return ProcEntry.th32ProcessID;
				spoof_return::close_handle(ProcSnap);
			}
		}

		spoof_return::close_handle(ProcSnap);
		return 0;
	}

	unsigned long get_proc_module_base(unsigned long proc_id, const wchar_t* module_name)
	{
		void* ModuleSnap = spoof_return::snap_proc_addr(TH32CS_SNAPMODULE, proc_id);
		if (ModuleSnap == INVALID_HANDLE_VALUE)
			return -1;

		MODULEENTRY32W ModuleEntry = {};
		ModuleEntry.dwSize = sizeof(MODULEENTRY32);

		if (spoof_return::module_first_w(ModuleSnap, &ModuleEntry) == FALSE)
			return -1;

		while (spoof_return::module_next_w(ModuleSnap, &ModuleEntry))
		{
			if (!wcscmp(ModuleEntry.szModule, module_name)) {
				return ModuleEntry.th32ModuleID;
				spoof_return::close_handle(ModuleSnap);
			}
		}

		spoof_return::close_handle(ModuleSnap);
		return 0;
	}
}