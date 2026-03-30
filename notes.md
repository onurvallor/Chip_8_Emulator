# NOTES from resources

- The Chip 8 has 35 opcodes which are all two bytes long.

- The Chip 8 has 4K memory in total

- The graphics of the Chip 8 are black and white and the screen has a total of 2048 pixels (64 x 32).

- The stack is used to remember the current location before a jump is performed. So anytime you perform a jump or call a subroutine, store the program counter in the stack before proceeding.

- The system has 16 levels of stack and in order to remember which level of the stack is used, you need to implement a stack pointer (sp).

- fetch two successive bytes and merge them to get the actual opcode.

- In order to merge both bytes and store them in an unsigned short (2 bytes datatype) we will use the bitwise OR operation

- Another important thing to remember is that the system expects the application to be loaded at memory location 0x200. This means that your program counter should also be set to this location.

-
