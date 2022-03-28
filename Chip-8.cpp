#include <fstream>
#include <iostream>
#include <iomanip>

#include "Chip-8.h"

void Chip8::execute_instruction(const Instruction& instruction)
{
    const unsigned char command_type = instruction.get_type();
    if (CLS == instruction.get_16bit_command())
    {
        std::cout << "Clear screen" << std::endl;
    }
    else if (JUMP == command_type)
    {
        _memory.set_program_counter(instruction.get_12bit_address());
        std::cout << "Jumping to " << std::setbase(16) << std::showbase << _memory.get_program_counter() << std::endl;
    }
    else if (SET_REGISTER == command_type)
    {
        _registers[instruction.get_x()] = instruction.get_8bit_number();
        std::cout << "Setting register " << int(instruction.get_x()) << " to " << int(_registers[instruction.get_x()]) << std::endl;
    }
    else if (ADD_TO_REGISTER == command_type)
    {
        int total = _registers[instruction.get_x()] + instruction.get_8bit_number();
        if (total > UCHAR_MAX)
        {
            total = UCHAR_MAX;
        }
        _registers[instruction.get_x()] = static_cast<unsigned char>(total);
        std::cout << "Adding " << int(instruction.get_8bit_number()) << " to register " << int(instruction.get_x()) << " to get " << int(_registers[instruction.get_x()]) << std::endl;
    }
    else if (SET_INDEX_REGISTER == command_type)
    {
        _memory.set_index_register(instruction.get_12bit_address());
        std::cout << "Setting index register to " << int(_memory.get_index_register()) << std::endl;

    }
    else if (DRAW == command_type)
    {
        std::cout << "Drawing to screen" << std::endl;
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

void Chip8::read_program_from_file_to_memory(const std::string filename)
{
    std::ifstream program;
    program.open(filename);
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
        _memory.write_data_at_current_index(c);
        _memory.set_index_register(_memory.get_index_register() + 1);
    }
    program.close();
    _memory.set_program_counter(PROGRAM_START);
}