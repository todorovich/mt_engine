// Copyright 2018 Micho Todorovich, all rights reserved.

#pragma once

#include "precompiled.hpp"

#include "InputMessage.hpp"

namespace mt::input
{
	class IM_KeyUp : public InputMessage
	{
	public:

		IM_KeyUp(WPARAM button_up)
			: InputMessage(static_cast<__int64>(button_up))
		{}

		IM_KeyUp(const IM_KeyUp& other)
			: InputMessage(other)
		{}

		IM_KeyUp(IM_KeyUp&& other)
			: InputMessage(std::move(other))
		{}

		~IM_KeyUp() = default;

		IM_KeyUp& operator=(const IM_KeyUp& other)
		{
			i64 = other.i64;

			return *this;
		}

		IM_KeyUp& operator=(IM_KeyUp&& other)
		{
			i64 = std::move(other.i64);

			return *this;
		}

		virtual void Execute()
		{
			_KeyUp(_button_up);
		};

	private:
		WPARAM & _button_up = *reinterpret_cast<WPARAM*>(&i64);
	};
}