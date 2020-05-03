#pragma once

#include "mt/precompiled.hpp"

#include "mt/time/Alarm.hpp"

namespace mt::time
{
	class Timer : public Alarm
	{		
	public:

		Timer(Duration offset, std::function<void()> callback)
			: Alarm(Clock::now() + offset, callback)
		{}

		~Timer() = default;

		Timer(const Timer& other) = delete;

		Timer(Timer&& other)
			: Alarm(std::move(other))
		{}

		Timer& operator=(const Timer& other) = delete;

		Timer& operator=(Timer&& other)
		{
			Alarm::operator=(std::move(other));
		};
	};
}