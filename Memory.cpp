#include <stdexcept>

#include "Memory.h"

const char16_t Memory::get_instruction() const
{
	char16_t instruction{ 0 };
	instruction = (_raw_data[_program_counter] << 8) | _raw_data[_program_counter + 1];
	return instruction;
}

const char16_t Memory::get_index_register() const
{
	return _index_register;
}
void Memory::set_index_register(const char16_t ir)
{
	if (ir < 0 || ir >= MAX_MEMORY_SIZE)
	{
		throw std::out_of_range("You cannot set the index register to outside memory");
	}
	_index_register = ir;
}

const char16_t Memory::get_program_counter() const
{
	return _program_counter;
}
void Memory::set_program_counter(const char16_t pc)
{
	if (pc < 0 || pc >= MAX_MEMORY_SIZE)
	{
		throw std::out_of_range("You cannot set the program counter to outside memory");
	}
	_program_counter = pc;
}
void Memory::increment_program_counter()
{
	_program_counter += 2;
}

void Memory::write_byte_at_current_index(const unsigned char data)
{
	_raw_data[_index_register] = data;
}

const unsigned char Memory::read_byte_at_current_index() const
{
	return _raw_data[_index_register];
}