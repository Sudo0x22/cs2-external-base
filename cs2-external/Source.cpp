#include"sdk/sdk.hpp"

namespace offsets
{
	uintptr_t m_dwEntityList = 0x00;
	uintptr_t m_dwLocalEntity = 0x00;
	uintptr_t m_vLocalOrigin = 0x00;
	uintptr_t m_iHealth = 0x00;
	uintptr_t m_iTeamNum = 0x00;

	uintptr_t m_vViewAngles = 0x00;
	uintptr_t m_vViewMatrix = 0x00;
	uintptr_t m_vViewRenderer = 0x00;
}

__inline Matrix GetViewMatrix(void* handle, uintptr_t addr, 
	uintptr_t view_render, uintptr_t view_matrix)
{
	uint64_t viewRenderer = memory::read_proc_mem<uint64_t>(handle, addr + view_render);
	uint64_t viewMatrix = memory::read_proc_mem<uint64_t>(handle, viewRenderer + view_matrix);
	return memory::read_proc_mem<Matrix>(handle, viewMatrix);
}

int main()
{
	unsigned long cs_proc = process::get_proc_base(L"cs2.exe");
	if (!cs_proc)
		fprintf(stderr, "Have CS2 Open\n");

	unsigned long cs_module = process::get_proc_module_base(cs_proc, L"cs2.exe");
	if (!cs_module)
		fprintf(stderr, "Make Sure CS2 Is Open\n");

	auto open_proc = HijackExistingHandle(cs_proc);
	if (open_proc == INVALID_HANDLE_VALUE)
		fprintf(stderr, "Failed To Open Handle\n");

	while (true)
	{
		auto local_entity = memory::read_proc_mem<uintptr_t>(open_proc, cs_module + offsets::m_dwLocalEntity);
		if (!local_entity)
			continue;

		for (int index = 1; index < 64; index++)
		{
			auto entity = memory::read_proc_mem<uintptr_t>(open_proc, cs_module + offsets::m_dwEntityList + (index << 5));
			if (!entity)
				continue;

			if (entity == local_entity)
				continue;

			auto local_team = memory::read_proc_mem<uintptr_t>(open_proc, local_entity + offsets::m_iTeamNum);
			auto entity_team = memory::read_proc_mem<uintptr_t>(open_proc, entity + offsets::m_iTeamNum);

			if (entity_team == local_team)
				continue;

			auto GetMatrix = GetViewMatrix(open_proc, cs_module, offsets::m_vViewRenderer, offsets::m_vViewMatrix);
			if (!GetMatrix.matrix)
				continue;


		}
			

	}
}