#pragma once
#ifndef CHIP_8_H
#define CHIP_8_H

#include <string>

#include "Constants.h"
#include "Display_Buffer.h"
#include "Instruction.h"
#include "Memory.h"
#include "Stack.h"
#include "Timer.h"
#include "Window.h"

class Chip8 
{
private:
	Memory _memory;
	Stack _stack;
	Registers _registers;
	Timer _delay_timer;
	Timer _sound_timer;
	DisplayBuffer _display;
	Window _window;
	
	std::string _current_program;

	void draw_to_display(const Instruction& instruction);
	void increment_conditional(const char16_t a, const char16_t b, const bool EQUAL);
	void process_logic_and_arithmetic(const Instruction& instruction);
	void check_underflow(const char16_t minuend, const char16_t subtrahend);
	void process_timer(const Instruction& instruction);
	void process_misc(const Instruction& instruction);
	const sf::Keyboard::Key get_keypad_entry();

public:
	Chip8();
	void execute_instruction(const Instruction& instruction);
	const char16_t fetch_instruction();
	void load_program_to_memory(const std::string filename);
	void run();
};

#endif