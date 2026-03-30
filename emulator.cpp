#include <array>
#include <iostream>

class Chip8 {
public:
  Chip8() { initialize(); }

  void initialize() {
    pc = 0x200; // Starting location
    opcode = 0;
    I = 0;
    sp = 0;

    for (int i = 0; i < 80; ++i) {
      // TODO: implement fontset.
      // memory[i] = chip8_fontset[i];
    }
  }

  void emulateCycle() {
    // fetch opcode by grabbing 2 bytes from PC and merging them using OR
    opcode = memory[pc] << 8 | memory[pc + 1];

    // mask the first nibble to get instruction of opcode
    switch (opcode & 0xF000) {

      // TODO: Add more opcodes

    case 0x0000:
      switch (opcode & 0x000F) {
      case 0x0000: // 0x00E0 clear screen
        // TODO: Implement clear screen opcode
        break;
      case 0x000E: // 0x00EE return from subroutine
        // TODO: Implement return from subroutine
        break;
      case 0x0004: // 0x8XY4 arithmetic add with carry.
                   // Move opcode bits of both X and Y to be at the right most
                   // nibble
        if (V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8])) {
          V[0xF] = 1; // carry flag
        } else {
          V[0x0F] = 0;
        }
        V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
        pc += 2;
        break;
      case 0x0006: // 0x8XY6 right shift and carry the LSB
                   // Right shift X value to the end of the hex and set V[F] to
                   // the LSB
        V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
        V[(opcode & 0x0F00) >> 8] >>= 1;
      default:
        std::cout << "Unknown opcode [0x0000]: 0x" << opcode << "\n";
        break;
      }
    case 0xA000: // Set I to address
      I = opcode & 0x0FFF;
      pc += 2;
      break;
    case 0x1000:
      pc = opcode & 0x0FFF;
      break;
    case 0x2000:            // Call subroutine
      stack[sp] = pc;       // store current address.
      ++sp;                 // increment to next instruction
      pc = opcode & 0x0FFF; // Set PC to address of next address from opcode.
      break;
    default:
      std::cerr << "Unknown opcode: 0x" << opcode << "\n";
    }

    // Update timers
    if (delay_timer > 0) {
      --delay_timer;
    }

    if (sound_timer > 0) {
      if (sound_timer == 1) {
        std::cout << "BEEP!\n";
        --sound_timer;
      }
    }
  }

private:
  // 2 byte opcode
  unsigned short opcode;

  std::array<unsigned char, 4096> memory;

  // CHIP 8 has 16 registers
  std::array<unsigned char, 16> V;

  // current instruction
  unsigned short I;

  // program counter
  unsigned short pc;

  // 2048 pixels (64x32) where each pixel only needs to hold a 1 or 0.
  std::array<unsigned char, 64 * 32> gfx;

  unsigned char delay_timer;
  unsigned char sound_timer;

  // 16 levels to the stack implementation
  std::array<unsigned short, 16> stack;
  // Stack pointer
  unsigned short sp;

  // HEX based keypad, stores current state of key
  std::array<unsigned char, 16> key;
};

int main() { return 0; }
