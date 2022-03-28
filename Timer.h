#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

#include "Constants.h"

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> _previous_time;
	char _timer;
	bool _active;
public:
	Timer() : _active{ true }, _timer{ static_cast<unsigned char>(0xF) }, _previous_time{ std::chrono::steady_clock::now() } {}
	void tick();
	void set(const unsigned char t);
	const unsigned char get() const;
};

#endif