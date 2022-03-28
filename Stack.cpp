#include "Stack.h"

void Stack::push(const char16_t addr)
{
	if (_position == STACK_SIZE)
	{
		throw std::length_error("Stack Overflow");
	}
	else if (addr < 0 || addr >= MAX_MEMORY_SIZE)
	{
		throw std::out_of_range("Storing a memory address outside of the bounds of memory is ill advised");
	}
	_stack[_position] = addr;
	++_position;
}

const char16_t Stack::pop()
{
	if (_position == 0)
	{
		return 0;
	}
	char16_t data = _stack[_position];
	_stack[_position] = 0;
	--_position;
	return data;
}
