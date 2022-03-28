#include "Timer.h"

void Timer::tick()
{
	if (_active == false)
	{
		return;
	}
	auto now_time = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> delta = now_time - _previous_time;
	if (delta.count() >= SIXTY_HZ)
	{
		if (_timer > 0)
		{
			--_timer;
		}
		else
		{
			_active = false;
		}
		_previous_time = now_time;
	}
}
void Timer::set(const unsigned char t)
{
	_timer = t;
	if (_timer != 0)
	{
		_active = true;
	}
}

const unsigned char Timer::get() const
{
	return _timer;
}