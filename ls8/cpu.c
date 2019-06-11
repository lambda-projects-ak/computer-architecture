#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *argv)
{
  // open file, read and load instructions into RAM
  FILE *fp;
  fp = fopen(argv, "r");
  char line[1024];

  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char *endptr;
    int index = 0;
    unsigned char file_output = strtoul(line, &endptr, 2);

    if (endptr == line)
    {
      // if this matches, the line must be blank
      continue;
    };

    // load memory here
    printf("%d\n", file_output);
    cpu->ram[index] = file_output;
    index++;
  };

  fclose(fp);

  for (int i = 0; i < 5; i++)
  {
    printf("%d\n", cpu->ram[i]);
  };
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
  int running = 1; // True until we get a HLT instruction
  unsigned char instruction;
  unsigned char operandA, operandB;

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    instruction = cpu->ram[cpu->pc];
    // 2. Figure out how many operands this next instruction requires
    // use first two numbers in binary to determine how many operands we need
    // 10 == 2
    // 01 == 1
    // 00 == 0

    // 3. Get the appropriate value(s) of the operands following this instruction
    if (instruction > 0b01111111)
    {
      operandA = cpu->ram[cpu->pc + 1];
      operandB = cpu->ram[cpu->pc + 2];
    }
    else if (instruction > 0b00111111)
    {
      operandA = cpu->ram[cpu->pc + 1];
    }
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
    switch (instruction)
    {
    case LDI:
      cpu->registers[operandA] = operandB;
      cpu->pc += 3;
      break;

    case PRN:
      printf("%d\n", cpu->registers[operandA]);
      cpu->pc += 2;
      break;

    case HLT:
      running = 0;
      break;

    default:
      printf("Unknown instruction %02x at address %02x\n", instruction, cpu->pc);
      exit(1);
    }
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