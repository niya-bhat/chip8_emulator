#include "chip8.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

Chip8::Chip8() {
    // power on reset
    std::memset(memory, 0, sizeof(memory));
    std::memset(V, 0, sizeof(V));
    std::memset(display, 0, sizeof(display));
    std::memset(keypad, 0, sizeof(keypad));
    std::memset(stack, 0, sizeof(stack));

    I = 0;
    sp = 0;
    delay_timer = 0;
    sound_timer = 0;
    
    // program counter
    pc = 0x200;

    InitializeFontMemory();
}

void Chip8::Cycle() {
    // Week 2 loop goes here
}

bool Chip8::LoadROM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Error: Failed to open ROM file: " << filename << std::endl;
        return false;
    }

    std::streampos size = file.tellg();
    
    const size_t MAX_ROM_SIZE = 4096 - 0x200; 
    if (static_cast<size_t>(size) > MAX_ROM_SIZE) {
        std::cerr << "Error: ROM size (" << size << " bytes) exceeds maximum allowable size." << std::endl;
        file.close();
        return false;
    }

    char* buffer = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    std::memcpy(&memory[0x200], buffer, size);
    delete[] buffer;

    std::cout << "Successfully loaded ROM: " << filename << " (" << size << " bytes)" << std::endl;
    return true;
}

void Chip8::InitializeFontMemory() {
    const uint8_t font_set[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    std::memcpy(&memory[0], font_set, sizeof(font_set));
}