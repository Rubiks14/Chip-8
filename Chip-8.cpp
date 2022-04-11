#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "Chip-8.h"

Chip8::Chip8() : _memory(), _stack(), _registers(), _delay_timer(), _sound_timer(), _current_program{ "" }, _window()
{
    _registers.fill(0);
    auto ir = _memory.get_index_register();
    for (auto i = 0; i < FONT_INFORMATION.size(); ++i)
    {
        _memory.set_index_register(FONT_LOCATION + i);
        _memory.write_byte_at_current_index(FONT_INFORMATION[i]);
    }
    _memory.set_index_register(ir);
}

void Chip8::draw_to_display(const Instruction& instruction)
{
    const char16_t initial_register = _memory.get_index_register();
    char16_t x = _registers[instruction.get_x()];
    char16_t y = _registers[instruction.get_y()];
    for (unsigned char i = 0; i < instruction.get_4bit_number(); ++i)
    {
        _memory.set_index_register(initial_register + i);
        _display.set_render_postion(x, y);
        const bool PIXEL_FLIPPED_OFF = _display.update_buffer(_memory.read_byte_at_current_index());
        _registers[FLAG_REGISTER] = PIXEL_FLIPPED_OFF ? 1 : 0;
        ++y;
    }
    _window.draw_buffer_on_screen(_display.get_buffer());
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
    {
        if (SET_VX_WHEN_SHIFTING)
        {
            _registers[instruction.get_x()] = _registers[instruction.get_y()];
        }
        auto old_vx = _registers[instruction.get_x()];
        std::bitset<8> byterep = old_vx;
        _registers[instruction.get_x()] >>= 1;
        _registers[FLAG_REGISTER] = old_vx == 1 || old_vx / 2 > _registers[instruction.get_x()] ? 1 : 0;
        break;
    }
    case SHIFT_LEFT:
    {
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
}

void Chip8::process_timer(const Instruction& instruction)
{
    switch (instruction.get_8bit_number())
    {
    case SET_VX_TO_DELAY_TIMER:
        _registers[instruction.get_x()] = _delay_timer.get();
        break;

    case SET_DELAY_TIMER_TO_VX:
        _delay_timer.set(_registers[instruction.get_x()]);
        break;

    case SET_SOUND_TIMER_TO_VX:
        _sound_timer.set(_registers[instruction.get_x()]);
        break;
    }
}

void Chip8::process_misc(const Instruction& instruction)
{
    switch (instruction.get_8bit_number())
    {
    case ADD_TO_INDEX:
        _memory.set_index_register(_memory.get_index_register() + _registers[instruction.get_x()]);
        break;
    case GET_KEY:
    {
        auto key = sf::Keyboard::Unknown;
        while (key == sf::Keyboard::Unknown)
        {
            key = get_keypad_entry();
        }
        _registers[instruction.get_x()] = key;
        break;
    }
    case FONT_CHARACTER:
        _memory.set_index_register(FONT_LOCATION + (_registers[instruction.get_x()]*5));
        break;
    case BINARY_CODED_DECIMAL:
    {
        auto original_register = _memory.get_index_register();
        auto number = _registers[instruction.get_x()];
        _memory.write_byte_at_current_index(number / 100);
        _memory.set_index_register(original_register + 1);
        _memory.write_byte_at_current_index(number % 100 / 10);
        _memory.set_index_register(original_register + 2);
        _memory.write_byte_at_current_index(number % 10);
        _memory.set_index_register(original_register);
        break;
    }
    case STORE_MEMORY:
    {
        auto original_register = _memory.get_index_register();
        for (unsigned char i = 0; i <= instruction.get_x(); ++i)
        {
            _memory.set_index_register(original_register + i);
            _memory.write_byte_at_current_index(static_cast<unsigned char>(_registers[i]));
        }
        _memory.set_index_register(original_register);
        break;
    }
    case LOAD_MEMORY:
    {
        auto original_register = _memory.get_index_register();
        for (unsigned char i = 0; i <= instruction.get_x(); ++i)
        {
            _memory.set_index_register(original_register + i);
            _registers[i] = _memory.read_byte_at_current_index();
        }
        _memory.set_index_register(original_register);
        break;
    }
    }
}

void Chip8::check_underflow(const char16_t minuend, const char16_t subtrahend)
{
    _registers[FLAG_REGISTER] = minuend > subtrahend ? 1 : 0;
}

const sf::Keyboard::Key Chip8::get_keypad_entry()
{
    auto key = _window.get_pressed_key();
    for (auto k : VALID_KEYS)
    {
        if (key == k)
        {
            return key;
        }
    }
    return sf::Keyboard::Unknown;
}

void Chip8::execute_instruction(const Instruction& instruction)
{
    const unsigned char command_type = instruction.get_type();
    if (CLS == instruction.get_16bit_command())
    {
        _display.clear();
        _window.clear();
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
        increment_conditional(_registers[instruction.get_x()], instruction.get_8bit_number(), true);
        break;

    case SKIP_IF_VX_NOEQUAL_NN:
        increment_conditional(_registers[instruction.get_x()], instruction.get_8bit_number(), false);
        break;

    case SKIP_IF_VX_EQUAL_VY:
        increment_conditional(_registers[instruction.get_x()], _registers[instruction.get_y()], true);
        break;
    
    case SKIP_IF_VX_NOEQUAL_VY:
        increment_conditional(_registers[instruction.get_x()], _registers[instruction.get_y()], false);
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

    case JUMP_WITH_OFFSET:
        _registers[0] += instruction.get_12bit_address();
        break;

    case RANDOM:
    {
        // RNG
        std::mt19937 mt;
        std::uniform_int_distribution<unsigned int> rng(0, 255);
        _registers[instruction.get_x()] &= rng(mt);
        break;
    }
    case DRAW:
        draw_to_display(instruction);
        break;
    case KEY_SKIP:
        switch (instruction.get_8bit_number())
        {
        case IF_VX_EQUAL_PRESSED_KEY:
            increment_conditional(_registers[instruction.get_x()], _window.get_pressed_key(), true);
            break;
        case IF_VX_NOEQUAL_PRESSED_KEY:
            increment_conditional(_registers[instruction.get_x()], _window.get_pressed_key(), false);
            break;
        }
        break;
    case TIMER_AND_MISC:
        process_timer(instruction);
        process_misc(instruction);

    }
    /***TODO: KEY PRESSES***/
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
    while (_window.check_window_state())
    {
        _delay_timer.tick();
        _sound_timer.tick();
        execute_instruction(fetch_instruction());
    }
}