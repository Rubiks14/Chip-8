#include <SFML/Window.hpp>

#include "Chip-8.h"

int main()
{
	Chip8 chip8;
	chip8.load_program_to_memory("BC_test.ch8");
	chip8.run();
}