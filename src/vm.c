#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu.h"
#include "instructions.h"

enum step_mode {
  AUTO = 0, MANUAL = 1
};

char fpeek(FILE* file) {
  char c = fgetc(stdin);
  ungetc(c, file);

  return c;
}

void printRegisters(CPU* cpu) {
  printf("%-4s %-4s %-4s %-4s %-4s %-4s %-4s %-4s %-4s %-4s %-4s\n",
    "R0", "R1", "R2", "R3", "R4", "R5", "AD", "RT", "IP", "FL", "SP");
  printf("%04X %04X %04X %04X %04X %04X %04X %04X %04X %04X %04X\n",
    read_reg(cpu, R0), read_reg(cpu, R1), read_reg(cpu, R2),
    read_reg(cpu, R3), read_reg(cpu, R4), read_reg(cpu, R5),
    read_reg(cpu, AD), read_reg(cpu, RT),
    read_reg(cpu, IP), read_reg(cpu, FL), read_reg(cpu, SP));
  printf("\n");
}

void printAddressByte(CPU* cpu, u_word start, u_word end) {
  if(start > end) {
    return;
  }

  for(uint64_t i = start; i <= end; i += 16) {
    printf("%04lX: ", i);
    for(uint64_t j = i; j < i + 16 && j <= end; j++) {
      printf("%02X ", cpu->address[j]);
    }
    printf("\n");
  }
  printf("\n");
}

void translate(const char* pathname, u_word* output, const u_word lines) {
  FILE* file;
  size_t length = 0;

  if((file = fopen(pathname, "r")) == NULL) {
    printf("Cannot open %s\n", pathname);
    return;
  }

  for(int i = 0; i < lines; i++) {
    char* buffer = NULL;
    getline(&buffer, &length, file);
    output[i] = strtol(buffer, NULL, 2);
    free(buffer);
  }

  fclose(file);
}

void run(CPU* cpu, enum step_mode mode) {
  while(1) {
    if(mode) {
      char buffer[16];
      u_word start;
      u_word end;

      if(fpeek(stdin) != '\n') {
        scanf("%[^\n]", buffer);
        if(sscanf(buffer, "%hx %hd", &start, &end) == 2) {
          printAddressByte(cpu, start, end);
        }
      }
      fgetc(stdin);
    }
    tick(cpu);
    printRegisters(cpu);
  }
}

int main(int argc, char** argv) {
  CPU cpu;
  int length = strtol(argv[1], NULL, 10);
  u_word code[length];

  if(argc != 3) {
    return -1;
  }

  cpu_reset(&cpu);
  map_instructions(&cpu);
  translate(argv[2], code, length);
  boot(&cpu, code, length);
  run(&cpu, MANUAL);
}
