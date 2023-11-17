#pragma once
#include"handle/hijack.hpp"
#include"spoofer/spoofer.hpp"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char JmpRbx[] = { 0xff, 0x23 };

namespace spoof_return
{
	FARPROC get_proc_addr(HMODULE hModule, LPCSTR ProcAddr) {
		auto return_addr = spoof_call_ex(JmpRbx, __safecall(GetProcAddress).get(), hModule, ProcAddr);
		return return_addr;
	}

	void* snap_proc_addr(unsigned long flags, unsigned long proc_id)
	{
		auto return_addr = spoof_call_ex(JmpRbx, __safecall(CreateToolhelp32Snapshot).get(), flags, proc_id);
		return return_addr;
	}

	bool proc_first_w(void* handle, LPPROCESSENTRY32W ProcEntry)
	{
		auto return_addr = spoof_call_ex(JmpRbx, __safecall(Process32FirstW).get(), handle, ProcEntry);
		return return_addr;
	}

	bool proc_next_w(void* handle, LPPROCESSENTRY32W ProcEntry)
	{
		auto return_addr = spoof_call_ex(JmpRbx, __safecall(Process32NextW).get(), handle, ProcEntry);
		return return_addr;
	}

	bool module_first_w(void* handle, LPMODULEENTRY32W ModuleEntry)
	{
		auto return_addr = spoof_call_ex(JmpRbx, __safecall(Module32FirstW).get(), handle, ModuleEntry);
		return return_addr;
	}

	bool module_next_w(void* handle, LPMODULEENTRY32W ModuleEntry)
	{
		auto return_addr = spoof_call_ex(JmpRbx, __safecall(Module32NextW).get(), handle, ModuleEntry);
		return return_addr;
	}

	bool close_handle(void* handle) {
		auto return_addr = spoof_call_ex(JmpRbx, __safecall(CloseHandle).get(), handle);
		return return_addr;
	}
}


namespace memory
{
	template<typename read>
	__inline read read_proc_mem(void* handle, uintptr_t addr)
	{
		read buffer = {};
		::ReadProcessMemory(handle, (void*)addr, (void*)buffer, sizeof(buffer), 0);
		return buffer;
	}

	template<typename write>
	__inline void write_proc_mem(void* handle, uintptr_t addr, write buffer)
	{
		::WriteProcessMemory(handle, addr, (void*)buffer, sizeof(buffer), 0);
	}
}