#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <bitset>
#include <climits>
#include <stdexcept>



const unsigned short STACK_SIZE{ 16 };
const unsigned short NUM_REGISTERS{ 16 };
const double SIXTY_HZ{ 1000.0 / 60.0 };
const unsigned short MAX_MEMORY_SIZE{ 4096 };
const unsigned short MAX_OPERATIONS_PER_MINUTE{ 700 };
const char16_t PROGRAM_START = 0x200;

using Registers = std::array<char16_t, NUM_REGISTERS>;
using HalfByte = std::bitset<4>;

// instruction types
const HalfByte CLS = 0x00E0;
const HalfByte JUMP = 0x1;
const HalfByte SET_REGISTER = 0x6;
const HalfByte ADD_TO_REGISTER = 0x7;
const HalfByte SET_INDEX_REGISTER = 0xA;
const HalfByte DRAW = 0xD;

#endif