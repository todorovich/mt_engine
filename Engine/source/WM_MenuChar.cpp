// Copyright 2018 Micho Todorovich, all rights reserved.

#include "WM_MenuChar.hpp"

LRESULT mt::WM_MenuChar::execute(const HWND & hwnd, const UINT & msg, const WPARAM & wParam, const LPARAM & lParam)
{
	return MAKELRESULT(0, MNC_CLOSE);
}