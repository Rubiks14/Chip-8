#pragma once
#ifndef DISPLAY_BUFFER_H
#define DISPLAY_BUFFER_H

#include <SFML/Graphics.hpp>

#include "Constants.h"

class DisplayBuffer
{
private:
	GraphicsBuffer _buffer;
	unsigned short _buffer_x, _buffer_y;
public:
	DisplayBuffer();
	void set_render_postion(const unsigned short x, const unsigned short y);
	const bool update_buffer(const unsigned short num_pixels);
	void display_buffer_in_console() const;
	void clear();
	const GraphicsBuffer get_buffer() const;
};

#endif
