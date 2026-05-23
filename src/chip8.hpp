#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>
#include <string>

class Chip8 {
public:
    Chip8();
    ~Chip8() = default;

    bool LoadROM(const std::string& filename);
    void Cycle();

    uint32_t display[64 * 32]; 
    uint8_t keypad[16];        

private:
    uint8_t memory[4096];      
    uint8_t V[16];             
    uint16_t I;                
    uint16_t pc;               

    uint16_t stack[16];        
    uint8_t sp;                

    uint8_t delay_timer;       
    uint8_t sound_timer;       

    void InitializeFontMemory();
};

#endif