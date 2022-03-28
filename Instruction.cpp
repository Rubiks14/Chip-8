#include "Instruction.h"

Instruction::Instruction(char16_t instruction_code) : _nibbles{ 0,0,0,0 }
{
	_nibbles[0] = instruction_code >> 12;
	_nibbles[1] = instruction_code << 4 >> 12;
	_nibbles[2] = instruction_code << 8 >> 12;
	_nibbles[3] = instruction_code << 12 >> 12;
}

const HalfByte& Instruction::operator[](const size_t i) const
{
	return _nibbles[i];
}
HalfByte& Instruction::operator[](const size_t i)
{
	return _nibbles[i];
}
const auto Instruction::begin() const
{
	return _nibbles.begin();
}
const auto Instruction::end() const
{
	return _nibbles.end();
}
const unsigned char Instruction::get_type() const
{
	return static_cast<unsigned char>(_nibbles[0].to_ulong());
}
const unsigned char Instruction::get_x() const
{
	return static_cast<unsigned char>(_nibbles[1].to_ulong());
}
const unsigned char Instruction::get_y() const
{
	return static_cast<unsigned char>(_nibbles[2].to_ulong());
}
const unsigned char Instruction::get_4bit_number() const
{
	return static_cast<unsigned char>(_nibbles[3].to_ulong());
}
const unsigned char Instruction::get_8bit_number() const
{
	unsigned long number{ 0 };
	number |= (_nibbles[2].to_ulong() << 4);
	number |= (_nibbles[3].to_ulong());
	return static_cast<unsigned char>(number);
}
const char16_t Instruction::get_12bit_address() const
{
	unsigned long addr{ 0 };
	addr |= (_nibbles[1].to_ulong() << 8);
	addr |= (_nibbles[2].to_ulong() << 4);
	addr |= (_nibbles[3].to_ulong());
	return static_cast<char16_t>(addr);
}
const char16_t Instruction::get_16bit_command() const
{
	unsigned long addr{ 0 };
	addr |= (_nibbles[0].to_ulong() << 12);
	addr |= (_nibbles[1].to_ulong() << 8);
	addr |= (_nibbles[2].to_ulong() << 4);
	addr |= (_nibbles[3].to_ulong());
	return static_cast<char16_t>(addr);
}