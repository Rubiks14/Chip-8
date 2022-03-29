#include <SFML/Window.hpp>

#include "Chip-8.h"

int main()
{
	Chip8 chip8;
	auto& window = chip8.get_window();
	
	chip8.read_program_from_file_to_memory("IBM Logo.ch8");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		chip8.execute_instruction(chip8.fetch_instruction());
	}
}