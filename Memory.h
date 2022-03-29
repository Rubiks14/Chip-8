#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include "Constants.h"

class Memory {
private:
	std::array<unsigned char, MAX_MEMORY_SIZE> _raw_data;
	char16_t _index_register;
	char16_t _program_counter;
public:
	Memory() : _raw_data(), _index_register{ 0 }, _program_counter{ 0 }
	{
		_raw_data.fill(0);
	}

	const char16_t get_instruction() const;

	const char16_t get_index_register() const;
	void set_index_register(const char16_t ir);

	const char16_t get_program_counter() const;
	void set_program_counter(const char16_t pc);
	void increment_program_counter();

	void write_byte_at_current_index(const unsigned char data);
	const unsigned char read_byte_at_current_index() const;

};


#endif