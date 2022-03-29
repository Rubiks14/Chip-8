#pragma once
#ifndef CHIP_8_H
#define CHIP_8_H

#include <string>

#include "Constants.h"
#include "Instruction.h"
#include "Memory.h"
#include "Stack.h"
#include "Timer.h"
#include "Display.h"

class Chip8 
{
private:
	Memory _memory;
	Stack _stack;
	Registers _registers;
	Timer _delay_timer;
	Display _display;
	std::string _current_program;
public:
	void execute_instruction(const Instruction& instruction);
	const char16_t fetch_instruction();
	void read_program_from_file_to_memory(const std::string filename);
	sf::RenderWindow& get_window();
};

#endif