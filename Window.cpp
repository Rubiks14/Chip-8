#include "Window.h"

Window::Window() : _window(sf::VideoMode(BUFFER_WIDTH * 10, BUFFER_HEIGHT * 10), "Chip-8")
{

}

void Window::draw_buffer_on_screen(const GraphicsBuffer buffer)
{
	for (auto i = 0; i < buffer.size(); ++i)
	{
		auto render_x = (i % BUFFER_WIDTH) * 10;
		auto render_y = (i / BUFFER_WIDTH) * 10;
		sf::RectangleShape pixel({ 10, 10 });
		pixel.setPosition(render_x, render_y);
		if (true == buffer[i])
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

const bool Window::check_window_state()
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

const sf::Keyboard::Key Window::get_pressed_key()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyReleased)
		{
			return event.key.code;
		}
	}
}

void Window::clear()
{
	_window.clear();
}