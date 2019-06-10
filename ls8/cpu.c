#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
  };

  int address = 0;

  // for (int i = 0; i < DATA_LEN; i++)
  // {
  //   cpu->ram[address++] = data[i];
  // }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 0; // True until we get a HLT instruction
  // int value, reg_location;

  for (int i = 0; i < 50; i++)
  {
    cpu_ram_read(cpu, i);
  }

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // unsigned char value = cpu->ram[cpu->pc]; // maybe?

    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  // 8 general-purpose 8-bit numeric registers R0-R7.
  memset(cpu->registers, 0, sizeof(unsigned char) * 8);
  // 8-bit addressing, so can address 256 bytes of RAM total
  memset(cpu->ram, 0, sizeof(unsigned char) * 256);
}

// RAM Methods
int cpu_ram_read(struct cpu *cpu, int index)
{
  if (index > 256 || index < 0)
  {
    printf("%s\n", "Index out of range.");
    return NULL;
  }

  printf("%d\n", cpu->ram[index]);
  return cpu->ram[index];
};

void cpu_ram_write(struct cpu *cpu, unsigned char element, int index)
{
  if (index > 256 || index < 0)
  {
    printf("%s\n", "Index out of range.");
  }

  cpu->ram[index] = element;
};