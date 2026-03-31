#ifndef CHIP8_H
#define CHIP8_H
#include <array>
class Chip8 {
public:
  Chip8();
  void initialize();
  void emulateCycle();

private:
  unsigned short opcode;

  std::array<unsigned char, 4096> memory;
  std::array<unsigned char, 16> V;

  unsigned short I;
  unsigned short pc;

  std::array<unsigned char, 64 * 32> gfx;

  unsigned char delay_timer;
  unsigned char sound_timer;

  std::array<unsigned short, 16> stack;

  unsigned short sp;

  std::array<unsigned char, 16> key;
};
#endif // !CHIP8_H
