#pragma once

#include "WindowsMessageHandler.hpp"

class WM_ENTERSIZEMOVE_Handler : public WindowsMessageHandler
{
	LRESULT execute(const HWND& hwnd, const UINT& msg, const WPARAM& wParam, const LPARAM& lParam);
};
