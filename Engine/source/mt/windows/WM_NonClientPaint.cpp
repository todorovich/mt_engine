// Copyright 2018 Micho Todorovich, all rights reserved.

#include "WM_NonClientPaint.hpp"

using namespace mt::windows;

LRESULT WM_NonClientPaint::execute(const HWND & hwnd, const UINT & msg, const WPARAM & wParam, const LPARAM & lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
