#include "cpu.h"

void cpu_reset(CPU* cpu) {
  for(int i = 0; i <= 0xFFFF; i++) {
    write_adr(cpu, i, 0, 1);
  }
  for(int i = 0; i < 8; i++) {
    write_reg(cpu, i, 0);
  }
  for(int i = 0; i < 128; i++) {
    cpu->instructions[i] = NULL;
  }
}

void boot(CPU* cpu, const u_word* code, const u_word length) {
  u_word size = sizeof(u_word);

  for(int i = 0; i < length; i++) {
    write_adr(cpu, size * i, code[i], size);
  }
}

u_word read_reg(CPU* cpu, const CPU_REGISTER reg) {
  u_word start = sizeof(u_word) * reg + (sizeof(u_word) - 1);
  u_word data = 0;

  for(u_word i = 0; i < sizeof(u_word); i++) {
    data |= cpu->registers[start - i] << (8 * i);
  }

  return data;
}

void write_reg(CPU* cpu, const CPU_REGISTER reg, const u_word data) {
  u_word start = sizeof(u_word) * reg + (sizeof(u_word) - 1);

  for(u_word i = 0; i < sizeof(u_word); i++) {
    cpu->registers[start - i] = (data >> (8 * i)) & 0xFF; // Shifts i-bytes then get last byte
  }
}

u_word read_adr(CPU* cpu, const u_word address, const u_byte bytes) {
  u_word start = sizeof(u_word) * address + (sizeof(u_word) - 1);
  u_word data = 0;

  for(u_word i = 0; i < bytes || i < sizeof(u_word); i++) {
    data |= cpu->memory[start - i] << (8 * i);
  }

  return data;
}

void write_adr(CPU* cpu, const u_word address, const u_word data, const u_byte bytes) {
  u_word start = sizeof(u_word) * address + (sizeof(u_word) - 1);

  for(u_word i = 0; i < bytes || i < sizeof(u_word); i++) {
    cpu->memory[start - i] = (data >> (8 * i)) & 0xFF; // Shifts i-bytes then get last byte
  }
}

u_word fetch(CPU* cpu) {
  u_word address = read_reg(cpu, IP);
  u_word hex = read_adr(cpu, address, sizeof(u_word));
  write_reg(cpu, IP, address + sizeof(u_word));
  return hex;
}

I_FORMAT* decode(CPU* cpu, const u_word hex) {
  return &((I_FORMAT) {
    .raw = hex
  });
}

void execute(CPU* cpu, const I_FORMAT* binary) {
  u_byte opcode = binary->s_type.opcode;
  cpu->instructions[opcode](cpu, binary);
}

void tick(CPU* cpu) {
  execute(cpu, decode(cpu, fetch(cpu)));
}
