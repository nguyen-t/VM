#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "instructions.h"

void printCode(u_word* code, u_word length) {
  for(int i = 0; i < length; i++) {
    printf("0x%04X\n", code[i]);
  }
}

void printRegisters(CPU* cpu) {
  printf("IP:\t0x%04X\n", read_reg(cpu, IP));
  printf("FL:\t0x%04X\n", read_reg(cpu, FL));
  printf("AC:\t0x%04X\n", read_reg(cpu, AC));
  printf("SP:\t0x%04X\n", read_reg(cpu, SP));
  printf("R0:\t0x%04X\n", read_reg(cpu, R0));
  printf("R1:\t0x%04X\n", read_reg(cpu, R1));
  printf("R2:\t0x%04X\n", read_reg(cpu, R2));
  printf("R3:\t0x%04X\n", read_reg(cpu, R3));
  printf("\n");
}

void printAddressByte(CPU* cpu, u_word start, u_word end) {
  for(u_word i = start; i <= end; i++) {
    printf("0x%04X:\t0x%02X\n", i, cpu->address[i]);
  }
  printf("\n");
}

void printAddressWord(CPU* cpu, u_word start, u_word end) {
  for(u_word i = start; i <= end; i += 2) {
    printf("0x%04X:\t0x%04X\n", i, read_adr(cpu, i, sizeof(u_word)));
  }
  printf("\n");
}

void printInstructions(CPU* cpu) {
  for(u_word i = 0; i < 128; i++) {
    printf("0x%04X:\t%p\n", i, cpu->instructions[i]);
  }
  printf("\n");
}

void translate(const char* pathname, u_word* output, const u_word lines) {
  FILE* file;
  size_t length = 0;

  if(lines < 1) {
    return;
  }

  if((file = fopen(pathname, "r")) == NULL) {
    printf("Cannot open %s\n", pathname);
    return;
  }

  for(int i = 0; i < lines; i++) {
    char* buffer;
    getline(&buffer, &length, file);
    output[i] = strtol(buffer, NULL, 2);
    free(buffer);
  }

  fclose(file);
}

void run(CPU* cpu, int repeats) {
  for(int i = 0; i < repeats; i++) {
    tick(cpu);
    printRegisters(cpu);
  }
}

int main(int argc, char** argv) {
  CPU cpu;
  int length = strtol(argv[2], NULL, 10);
  u_word code[length];

  if(argc != 3) {
    return -1;
  }

  cpu_reset(&cpu);
  map_instructions(&cpu);
  translate(argv[1], code, length);
  boot(&cpu, code, length);
  printAddressByte(&cpu, 0x0000, (length * 2) - 1);
  run(&cpu, 25);
}
