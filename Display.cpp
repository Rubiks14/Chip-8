#include "Display.h"
#include <iostream>

Display::Display() : _window(sf::VideoMode(BUFFER_WIDTH * 10, BUFFER_HEIGHT * 10), "Chip-8"), _buffer{}, _buffer_x{ 0 }, _buffer_y{ 0 } 
{
	_buffer.fill(0);
}
void Display::set_render_postion(const unsigned short x, const unsigned short y)
{
	_buffer_x = x % BUFFER_WIDTH;
	_buffer_y = y % BUFFER_HEIGHT;
}
const bool Display::update_buffer(const unsigned short num_pixels)
{
	Byte pixel_data{ num_pixels };
	bool flag_status = false;
	auto x = _buffer_x;
	auto y = _buffer_y;
	for (int i = pixel_data.size() - 1; i >= 0; --i)
	{
		if (x >= BUFFER_WIDTH || y >= BUFFER_HEIGHT)
		{
			break;
		}
		if (_buffer[y * BUFFER_WIDTH + x] == true && pixel_data[i] == true)
		{
			flag_status = true;
		}
		_buffer[y * BUFFER_WIDTH + x] ^= pixel_data[i] ? true : false;
		++x;
		
	}
	return flag_status;
}

void Display::display_buffer_in_console() const
{
	for (auto i = 0; i < _buffer.size(); ++i)
	{
		if (i % BUFFER_WIDTH == 0)
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
		auto render_x = (i % BUFFER_WIDTH) * 10;
		auto render_y = (i / BUFFER_WIDTH) * 10;
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

const bool Display::check_window_state()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window.close();
			return false;
		}
	}
	return true;
}