#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>

#include "Constants.h"

class Display
{
private:
	sf::RenderWindow _window;
	std::array<bool, DISPLAY_WIDTH* DISPLAY_HEIGHT> _buffer;
	unsigned short _buffer_x, _buffer_y;
public:
	Display();
	sf::RenderWindow& get_window() { return _window; }
	void set_render_postion(const unsigned short x, const unsigned short y);
	void update_buffer(const unsigned short num_pixels);
	void display_buffer_in_console() const;
	void clear();
	void display_buffer_on_screen();
};

#endif
