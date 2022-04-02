#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>

#include "Constants.h"

class Display
{
private:
	sf::RenderWindow _window;
	std::array<bool, BUFFER_WIDTH * BUFFER_HEIGHT> _buffer;
	unsigned short _buffer_x, _buffer_y;
public:
	Display();
	void set_render_postion(const unsigned short x, const unsigned short y);
	const bool update_buffer(const unsigned short num_pixels);
	void display_buffer_in_console() const;
	void clear();
	void display_buffer_on_screen();
	const bool check_window_state();
};

#endif
