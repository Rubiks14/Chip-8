#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Chip-8.h"

int main()
{
	Chip8 chip8;

	//chip8.execute_instruction(chip8.fetch_instruction());
	
	chip8.read_program_from_file_to_memory("IBM Logo.ch8");
	while (true)
	{
		chip8.execute_instruction(chip8.fetch_instruction());
	}
}