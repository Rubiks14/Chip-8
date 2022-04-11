#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <bitset>
#include <climits>
#include <random>
#include <stdexcept>
#include <SFML/Window/Keyboard.hpp>

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
const char16_t FONT_LOCATION = 0x50;

// types
using Registers = std::array<unsigned char, NUM_REGISTERS>;
using HalfByte = std::bitset<4>;
using Byte = std::bitset<8>;
using GraphicsBuffer = std::array<bool, BUFFER_WIDTH * BUFFER_HEIGHT>;

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

// all logical and arithmetic instructions
const unsigned char ARITHMETIC_INSTRUCTIONS{ 0x8 };
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
const unsigned char JUMP_WITH_OFFSET{ 0xB };
const unsigned char RANDOM{ 0xC };
const unsigned char DRAW{ 0xD };

// all key skip instructions;
const unsigned char KEY_SKIP{ 0xE };
const unsigned char IF_VX_EQUAL_PRESSED_KEY{ 0x9E };
const unsigned char IF_VX_NOEQUAL_PRESSED_KEY{ 0xA1 };

// all timer related instructions
const unsigned char TIMER_AND_MISC{ 0xF };
const unsigned char SET_VX_TO_DELAY_TIMER{ 0x07 };
const unsigned char SET_DELAY_TIMER_TO_VX{ 0x15 };
const unsigned char SET_SOUND_TIMER_TO_VX{ 0x18 };

// misc functions that share 0xF instruction
const unsigned char ADD_TO_INDEX{ 0x1E };
const unsigned char GET_KEY{ 0x0A };
const unsigned char FONT_CHARACTER{ 0x29 };
const unsigned char BINARY_CODED_DECIMAL{ 0x33 };
const unsigned char STORE_MEMORY{ 0x55 };
const unsigned char LOAD_MEMORY{ 0x65 };

const std::array<unsigned char, 5 * 16> FONT_INFORMATION =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

enum KEYS
{
	ONE = sf::Keyboard::Num1,
	TWO = sf::Keyboard::Num2,
	THREE = sf::Keyboard::Num3,
	C = sf::Keyboard::Num4,
	FOUR = sf::Keyboard::Q,
	FIVE = sf::Keyboard::W,
	SIX = sf::Keyboard::E,
	D = sf::Keyboard::R,
	SEVEN = sf::Keyboard::A,
	EIGHT = sf::Keyboard::S,
	NINE = sf::Keyboard::D,
	E = sf::Keyboard::F,
	A = sf::Keyboard::Z,
	ZERO = sf::Keyboard::X,
	B = sf::Keyboard::C,
	F = sf::Keyboard::V
};

const std::array<int, 16> VALID_KEYS = { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D, E };

#endif