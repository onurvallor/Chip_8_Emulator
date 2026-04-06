#include "Chip8.hpp"
#include <array>
#include <iostream>

Chip8::Chip8() { initialize(); }

void Chip8::initialize() {
  pc = 0x200; // Starting location
  opcode = 0;
  I = 0;
  sp = 0;

  memory.fill(0);
  V.fill(0);
  gfx.fill(0);
  stack.fill(0);
  key.fill(0);

  for (int i = 0; i < 80; ++i) {
    // TODO: implement fontset.
    // memory[i] = chip8_fontset[i];
  }
}

void Chip8::emulateCycle() {
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
    default:
      std::cout << "Unknown opcode [0x0000]: 0x" << opcode << "\n";
      break;
    }
    break;
  case 0x8000:

    switch (opcode & 0x000F) {

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
    }
    break;
  case 0x0007: // Subtract VX from VY and if borrow occured set VF to 1, else 0.
    if ((V[(opcode & 0x0F00) >> 8]) <= (V[opcode & 0x00F0 >> 4])) {
      V[0xF] = 0; // borrow occured
    } else {
      V[0xF] = 1; // borrow has not occured
    }
    V[(opcode & 0x0F00)] =
        V[(opcode & 0x0F00) >> 8] - V[(opcode & 0x00F0) >> 4];
    break;
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

// source:
// https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
unsigned char chip8_fontset[80] = {
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
