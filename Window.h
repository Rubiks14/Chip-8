#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "Constants.h"

class Window
{
private:
	sf::RenderWindow _window;
public:
	Window();
	void draw_buffer_on_screen(const GraphicsBuffer buffer);
	const bool check_window_state();
	const sf::Keyboard::Key get_pressed_key();
	void clear();
};

#endif