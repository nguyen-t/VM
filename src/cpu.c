#include "cpu.h"

void cpu_reset(CPU* cpu) {
  for(unsigned int i = 0; i <= 0xFFFFu; i++) {
    write_adr(cpu, i, 0, 1);
  }
  for(unsigned int i = 0; i < 12; i++) {
    write_reg(cpu, i, 0);
  }
  for(unsigned int i = 0; i < 128; i++) {
    cpu->instructions[i] = NULL;
  }

  write_reg(cpu, SP, ADDRESS_STACK);
  write_reg(cpu, FP, ADDRESS_STACK);
  write_reg(cpu, IP, ADDRESS_ROM);
  write_reg(cpu, FL, 0x0000u);
}

void boot(CPU* cpu, const u_word* code, const u_word length) {
  u_word size = sizeof(u_word);

  for(int i = 0; i < length; i++) {
    cpu->address[ADDRESS_ROM + i * size + 0] = code[i] >> 8;
    cpu->address[ADDRESS_ROM + i * size + 1] = code[i] >> 0;
  }
}

u_word read_reg(CPU* cpu, const CPU_REGISTER reg) {
  return cpu->registers[reg];
}

void write_reg(CPU* cpu, const CPU_REGISTER reg, const u_word data) {
  cpu->registers[reg] = data;
}

u_word read_adr(CPU* cpu, const u_word address, const u_byte bytes) {
  u_word data = 0;

  for(u_word i = 0; i < bytes || i < sizeof(u_word); i++) {
    data |= cpu->address[address + i] << (8 * i);
  }

  return data;
}

void write_adr(CPU* cpu, const u_word address, const u_word data, const u_byte bytes) {
  for(u_word i = 0; i < bytes || i < sizeof(u_word); i++) {
    cpu->address[address + i] = (data >> (8 * i)) & 0x00FFu;
  }
}

u_word fetch(CPU* cpu) {
  u_word address = read_reg(cpu, IP);
  u_word hex = read_adr(cpu, address, sizeof(u_word));
  write_reg(cpu, IP, address + sizeof(u_word));
  return hex;
}

OP decode(CPU* cpu, const u_word hex) {
  return (OP) {
    .raw = hex
  };
}

void execute(CPU* cpu, const OP binary) {
  u_byte opcode = binary.s_type.opcode;
  cpu->instructions[opcode](cpu, binary);
}

void tick(CPU* cpu) {
  execute(cpu, decode(cpu, fetch(cpu)));
}
