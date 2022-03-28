#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "Constants.h"

class Instruction
{
private:
	std::array<HalfByte, 4> _nibbles;
public:
	Instruction(char16_t instruction_hex);
	const HalfByte& operator[](const size_t i) const;
	HalfByte& operator[](const size_t i);
	const auto begin() const;
	const auto end() const;
	const unsigned char get_type() const;
	const unsigned char get_x() const;
	const unsigned char get_y() const;
	const unsigned char get_4bit_number() const;
	const unsigned char get_8bit_number() const;
	const char16_t get_12bit_address() const;
	const char16_t get_16bit_command() const;
};

#endif