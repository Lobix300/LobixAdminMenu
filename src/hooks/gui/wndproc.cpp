#include "hooking.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include "asi_loader/scriptmanager.hpp"

namespace big
{
	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->wndproc(hwnd, msg, wparam, lparam);
				ScriptManager::WndProc(hwnd, msg, wparam, lparam);
			}

			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
		} EXCEPT_CLAUSE

		return NULL;
	}
}
