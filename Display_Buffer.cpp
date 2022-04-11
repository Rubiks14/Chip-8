#include "Display_Buffer.h"
#include <iostream>

DisplayBuffer::DisplayBuffer() : _buffer{}, _buffer_x{ 0 }, _buffer_y{ 0 } 
{
	_buffer.fill(0);
}
void DisplayBuffer::set_render_postion(const unsigned short x, const unsigned short y)
{
	_buffer_x = x % BUFFER_WIDTH;
	_buffer_y = y % BUFFER_HEIGHT;
}
const bool DisplayBuffer::update_buffer(const unsigned short num_pixels)
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

void DisplayBuffer::display_buffer_in_console() const
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

void DisplayBuffer::clear()
{
	_buffer.fill(0);
}

const GraphicsBuffer DisplayBuffer::get_buffer() const
{
	return _buffer;
}