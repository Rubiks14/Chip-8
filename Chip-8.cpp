#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "Chip-8.h"

void Chip8::draw_to_display(const Instruction& instruction)
{
    const char16_t initial_register = _memory.get_index_register();
    unsigned char x = _registers[instruction.get_x()];
    unsigned char y = _registers[instruction.get_y()];
    for (unsigned char i = 0; i < instruction.get_4bit_number(); ++i)
    {
        _memory.set_index_register(initial_register + i);
        _display.set_render_postion(x, y);
        const bool PIXEL_FLIPPED_OFF = _display.update_buffer(_memory.read_byte_at_current_index());
        _registers[FLAG_REGISTER] = PIXEL_FLIPPED_OFF ? 1 : 0;
        ++y;
    }
    _display.display_buffer_in_console();
    _display.display_buffer_on_screen();
    _memory.set_index_register(initial_register);
}

void Chip8::increment_conditional(const char16_t a, const char16_t b, const bool EQUAL)
{
    if ((a == b) == EQUAL)
    {
        _memory.increment_program_counter();
    }
}

void Chip8::process_logic_and_arithmetic(const Instruction& instruction)
{
    switch (instruction.get_4bit_number())
    {
    case SET_VX_TO_VY:
        _registers[instruction.get_x()] = _registers[instruction.get_y()];
        break;
    
    case BINARY_OR:
        _registers[instruction.get_x()] |= _registers[instruction.get_y()];
        break;

    case BINARY_AND:
        _registers[instruction.get_x()] &= _registers[instruction.get_y()];
        break;

    case BINARY_XOR:
        _registers[instruction.get_x()] ^= _registers[instruction.get_y()];
        break;

    case ADD:
        _registers[instruction.get_x()] += _registers[instruction.get_y()];
        _registers[FLAG_REGISTER] = _registers[instruction.get_x()] > 0xFF ? 1 : 0;
        break;

    case SUBRTACT_VY_FROM_VX:
        check_underflow(_registers[instruction.get_x()], _registers[instruction.get_y()]);
        _registers[instruction.get_y()] -= _registers[instruction.get_x()];
        break;

    case SUBTRACT_VX_FROM_VY:
        check_underflow(_registers[instruction.get_y()], _registers[instruction.get_x()]);
        _registers[instruction.get_x()] -= _registers[instruction.get_y()];
        break;

    case SHIFT_RIGHT:
        if (SET_VX_WHEN_SHIFTING)
        {
            _registers[instruction.get_x()] = _registers[instruction.get_y()];
        }
        auto old_vx = _registers[instruction.get_x()];
        _registers[instruction.get_x()] >>= 1;
        _registers[FLAG_REGISTER] = old_vx / 2 > _registers[instruction.get_x()] ? 1 : 0;
        break;

    case SHIFT_LEFT:
        if (SET_VX_WHEN_SHIFTING)
        {
            _registers[instruction.get_x()] = _registers[instruction.get_y()];
        }
        auto old_vx = _registers[instruction.get_x()];
        _registers[instruction.get_x()] <<= 1;
        _registers[FLAG_REGISTER] = old_vx > _registers[instruction.get_x()] ? 1 : 0;

        break;
    }
}

void Chip8::check_underflow(const char16_t minuend, const char16_t subtrahend)
{
    _registers[FLAG_REGISTER] = minuend > subtrahend ? 1 : 0;
}

void Chip8::execute_instruction(const Instruction& instruction)
{
    const unsigned char command_type = instruction.get_type();
    if (CLS == instruction.get_16bit_command())
    {
        _display.clear();
        return;
    }
    else if (RETURN == instruction.get_16bit_command())
    {
        _memory.set_program_counter(_stack.pop());
        return;
    }
    switch (command_type)
    {
    case JUMP:
        _memory.set_program_counter(instruction.get_12bit_address());
        break;

    case CALL:
        _stack.push(_memory.get_program_counter());
        _memory.set_program_counter(instruction.get_12bit_address());
        break;

    case SKIP_IF_VX_EQUAL_NN:
        increment_conditional(instruction.get_x(), instruction.get_8bit_number(), true);
        break;

    case SKIP_IF_VX_NOEQUAL_NN:
        increment_conditional(instruction.get_x(), instruction.get_8bit_number(), false);
        break;

    case SKIP_IF_VX_EQUAL_VY:
        increment_conditional(instruction.get_x(), instruction.get_y(), true);
        break;
    
    case SKIP_IF_VX_NOEQUAL_VY:
        increment_conditional(instruction.get_x(), instruction.get_y(), false);
        break;

    case SET_REGISTER:
        _registers[instruction.get_x()] = instruction.get_8bit_number();
        break;

    case ADD_TO_REGISTER:
    {
        int total = _registers[instruction.get_x()] + instruction.get_8bit_number();
        if (total > UCHAR_MAX)
        {
            total = UCHAR_MAX;
        }
        _registers[instruction.get_x()] = static_cast<unsigned char>(total);
        break;
    }
    case ARITHMETIC_INSTRUCTIONS:
        process_logic_and_arithmetic(instruction);
        break;

    case SET_INDEX_REGISTER:
        _memory.set_index_register(instruction.get_12bit_address());
        break;

    case DRAW:
        draw_to_display(instruction);
        break;
    }
}

const char16_t Chip8::fetch_instruction()
{
    if (_memory.get_program_counter() >= 4096)
    {
        std::cout << "end of program " << std::endl;
        abort();
    }
    char16_t instruction = _memory.get_instruction();
    _memory.increment_program_counter();
    return instruction;
}

void Chip8::load_program_to_memory(const std::string filename)
{
    std::ifstream program;
    program.open(filename, std::fstream::binary);
    if (!program.is_open())
    {
        std::cerr << "Unable to open file '" << filename << "'" << std::endl;
        abort();
    }
    _memory.set_index_register(PROGRAM_START);
    std::string data_string{ "" };
    std::getline(program, data_string);
    for (unsigned char c : data_string)
    {
        _memory.write_byte_at_current_index(c);
        _memory.set_index_register(_memory.get_index_register() + 1);
    }
    program.close();
    _memory.set_program_counter(PROGRAM_START);
}

void Chip8::run()
{
    while (_display.check_window_state())
    {
        execute_instruction(fetch_instruction());
    }
}