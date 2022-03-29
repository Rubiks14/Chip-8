#include "Display.h"
#include <iostream>

Display::Display() : _window(sf::VideoMode(DISPLAY_WIDTH * 10, DISPLAY_HEIGHT * 10), "Chip-8"), _buffer{}, _buffer_x{ 0 }, _buffer_y{ 0 } 
{
	_buffer.fill(0);
}
void Display::set_render_postion(const unsigned short x, const unsigned short y)
{
	_buffer_x = x % DISPLAY_WIDTH;
	_buffer_y = y % DISPLAY_HEIGHT;
}
void Display::update_buffer(const unsigned short num_pixels)
{
	Byte pixel_data{ num_pixels };
	auto x = _buffer_x;
	auto y = _buffer_y;
	for (int i = pixel_data.size() - 1; i >= 0; --i)
	{
		if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT)
		{
			break;
		}
		_buffer[y * DISPLAY_WIDTH + x] ^= pixel_data[i] ? true : false;
		++x;
		
	}
}

void Display::display_buffer_in_console() const
{
	for (auto i = 0; i < _buffer.size(); ++i)
	{
		if (i % DISPLAY_WIDTH == 0)
		{
			std::cout << std::endl;
		}
		std::cout << _buffer[i];
	}
	std::cout << std::endl;
}

void Display::clear()
{
	_buffer.fill(0);
	_window.clear();
}
void Display::display_buffer_on_screen()
{
	for (auto i = 0; i < _buffer.size(); ++i)
	{
		auto render_x = (i % DISPLAY_WIDTH) * 10;
		auto render_y = (i / DISPLAY_WIDTH) * 10;
		sf::RectangleShape pixel({ 10, 10 });
		pixel.setPosition(render_x, render_y);
		if (true == _buffer[i])
		{
			pixel.setFillColor(sf::Color(255, 255, 255));
			pixel.setOutlineColor(sf::Color(0, 0, 0));
			pixel.setOutlineThickness(1.0f);
			
		}
		else 
		{
			pixel.setFillColor(sf::Color(0, 0, 0));
		}
		_window.draw(pixel);
	}
	_window.display();
}
