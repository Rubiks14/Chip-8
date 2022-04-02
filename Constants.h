#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <bitset>
#include <climits>
#include <stdexcept>

using Registers = std::array<char16_t, NUM_REGISTERS>;
using HalfByte = std::bitset<4>;
using Byte = std::bitset<8>;

// constants representing specs
const unsigned short BUFFER_WIDTH{ 64 };
const unsigned short BUFFER_HEIGHT{ 32 };
const unsigned short STACK_SIZE{ 16 };
const unsigned short NUM_REGISTERS{ 16 };
const unsigned short FLAG_REGISTER{ 15 };
const double SIXTY_HZ{ 1000.0 / 60.0 };
const unsigned short MAX_MEMORY_SIZE{ 4096 };
const unsigned short MAX_OPERATIONS_PER_MINUTE{ 700 };
const char16_t PROGRAM_START = 0x200;

// configuration constants
const bool SET_VX_WHEN_SHIFTING = false;

// instruction types
const char16_t CLS{ 0x00E0 };
const char16_t RETURN{ 0x00EE };
const unsigned char JUMP{ 0x1 };
const unsigned char CALL{ 0x2 };
const unsigned char SKIP_IF_VX_EQUAL_NN{ 0x3 };
const unsigned char SKIP_IF_VX_NOEQUAL_NN{ 0x4 };
const unsigned char SKIP_IF_VX_EQUAL_VY{ 0x5 };
const unsigned char SKIP_IF_VX_NOEQUAL_VY{ 0x9 };
const unsigned char SET_REGISTER{ 0x6 };
const unsigned char ADD_TO_REGISTER{ 0x7 };
const unsigned char ARITHMETIC_INSTRUCTIONS{ 0x8 };

// all logical and arithmetic instructions;
const unsigned char SET_VX_TO_VY{ 0x0 };
const unsigned char BINARY_OR{ 0x1 };
const unsigned char BINARY_AND{ 0x2 };
const unsigned char BINARY_XOR{ 0x3 };
const unsigned char ADD{ 0x4 };
const unsigned char SUBRTACT_VY_FROM_VX{ 0x5 };
const unsigned char SUBTRACT_VX_FROM_VY{ 0x7 };
const unsigned char SHIFT_RIGHT{ 0x6 };
const unsigned char SHIFT_LEFT{ 0xE };

const unsigned char SET_INDEX_REGISTER{ 0xA };
const unsigned char DRAW{ 0xD };

#endif