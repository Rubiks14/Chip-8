#pragma once
#ifndef STACK_H
#define STACK_H

#include "Constants.h"

class Stack
{
private:
	std::array<char16_t, STACK_SIZE> _stack;
	unsigned char _position;
public:
	Stack() : _stack(), _position{ 0 }
	{
		_stack.fill(0);
	}

	void push(const char16_t addr);
	const char16_t pop();
};

#endif