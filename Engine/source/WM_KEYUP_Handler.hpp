#pragma once

#include "WindowsMessageHandler.hpp"

namespace mt
{
	class WM_KEYUP_Handler : public WindowsMessageHandler
	{
		LRESULT execute(const HWND& hwnd, const UINT& msg, const WPARAM& wParam, const LPARAM& lParam);
	};
}