#include "instructions.h"

/* Special instructions */
static void hlt(CPU* cpu, const I_FORMAT* ins) {
  while(1);
}


/* Register management instrucions */
static void li0(CPU* cpu, const I_FORMAT* ins) {
  u_word data = ins->i_type.immv;
  u_word shift = ins->i_type.extra * 8;
  u_word current = read_reg(cpu, R0);
  current &= (0xFF00u >> shift);
  current |= (data << shift);
  write_reg(cpu, R0, current);
}

static void li1(CPU* cpu, const I_FORMAT* ins) {
  u_word data = ins->i_type.immv;
  u_word shift = ins->i_type.extra * 8;
  u_word current = read_reg(cpu, R1);
  current &= (0xFF00u >> shift);
  current |= (data << shift);
  write_reg(cpu, R1, current);
}

static void li2(CPU* cpu, const I_FORMAT* ins) {
  u_word data = ins->i_type.immv;
  u_word shift = ins->i_type.extra * 8;
  u_word current = read_reg(cpu, R2);
  current &= (0xFF00u >> shift);
  current |= (data << shift);
  write_reg(cpu, R2, current);
}

static void li3(CPU* cpu, const I_FORMAT* ins) {
  u_word data = ins->i_type.immv;
  u_word shift = ins->i_type.extra * 8;
  u_word current = read_reg(cpu, R3);
  current &= (0xFF00u >> shift);
  current |= (data << shift);
  write_reg(cpu, R3, current);
}

static void li4(CPU* cpu, const I_FORMAT* ins) {
  u_word data = ins->i_type.immv;
  u_word shift = ins->i_type.extra * 8;
  u_word current = read_reg(cpu, R4);
  current &= (0xFF00u >> shift);
  current |= (data << shift);
  write_reg(cpu, R4, current);
}

static void li5(CPU* cpu, const I_FORMAT* ins) {
  u_word data = ins->i_type.immv;
  u_word shift = ins->i_type.extra * 8;
  u_word current = read_reg(cpu, R5);
  current &= (0xFF00u >> shift);
  current |= (data << shift);
  write_reg(cpu, R5, current);
}

static void lia(CPU* cpu, const I_FORMAT* ins) {
  u_word data = ins->i_type.immv;
  u_word shift = ins->i_type.extra * 8;
  u_word current = read_reg(cpu, AD);
  current &= (0xFF00u >> shift);
  current |= (data << shift);
  write_reg(cpu, AD, current);
}


/* Read/write instructions */
static void ldb(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word address = read_reg(cpu, reg1);
  u_word data = read_adr(cpu, address, 1);
  write_reg(cpu, reg2, data);
}

static void ldw(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word address = read_reg(cpu, reg1);
  u_word data = read_adr(cpu, address, sizeof(u_word));
  write_reg(cpu, reg2, data);
}

static void stb(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word address = read_reg(cpu, reg2);
  u_word data = read_reg(cpu, reg1);
  write_adr(cpu, address, data, 1);
}

static void stw(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word address = read_reg(cpu, reg2);
  u_word data = read_reg(cpu, reg1);
  write_adr(cpu, address, data, sizeof(u_word));
}

static void psh(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word address = read_reg(cpu, SP);
  u_word data = read_reg(cpu, reg2);
  write_adr(cpu, address, data, 2);
  write_reg(cpu, SP, SP - 2);
}

static void pop(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word address = read_reg(cpu, SP);
  u_word data = read_adr(cpu, address + 2, 2);
  write_reg(cpu, reg2, data);
  write_reg(cpu, SP, SP - 2);
}


/* Arithmetic instrucions */
static void cmp(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  u_word flag = read_reg(cpu, FL) & 0x0FF8u;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  word results = data1 - data0;

  if(results == 0) {
    flag |= 0x0001u;
  } else if(results > 0) {
    flag |= 0x0002u;
  } else if(results < 0) {
    flag |= 0x0004u;
  }

  write_reg(cpu, FL, flag);
}

static void not(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word data = read_reg(cpu, reg1);
  write_reg(cpu, reg2, ~data);
}

static void orr(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word data0 = read_reg(cpu, reg0);
  u_word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 | data0);
}

static void and(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word data0 = read_reg(cpu, reg0);
  u_word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 & data0);
}

static void xor(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word data0 = read_reg(cpu, reg0);
  u_word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 ^ data0);
}

static void add(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 + data0);
}

static void sub(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 - data0);
}

static void mul(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 * data0);
}

static void div(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 / data0);
}

static void lsl(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 << data0);
}

static void lsr(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  write_reg(cpu, reg2, data1 >> data0);
}


/* Control instructions */
static void jmp(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word current = read_reg(cpu, IP);
  u_word offset = read_reg(cpu, reg2) - 2;
  write_reg(cpu, IP, current + offset);
}

static void jsr(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg2 = ins->r_type.reg2;
  u_word current = read_reg(cpu, IP);
  u_word offset = read_reg(cpu, reg2) - 2;
  write_reg(cpu, RT, current);
  write_reg(cpu, IP, current + offset);
}

static void beq(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data = read_reg(cpu, reg2);
  u_word current = read_reg(cpu, IP);
  u_word flag = (read_reg(cpu, FL) & 0x0001u) ? 1 : 0;
  word offset = flag * (data - 2);
  write_reg(cpu, IP, current + offset);
}

static void bgt(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data = read_reg(cpu, reg2);
  u_word current = read_reg(cpu, IP);
  u_word flag = (read_reg(cpu, FL) & 0x0002u) ? 1 : 0;
  word  offset = flag * data;
  write_reg(cpu, IP, current + offset);
}

static void blt(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg2 = ins->r_type.reg2;
  word data = read_reg(cpu, reg2);
  u_word current = read_reg(cpu, IP);
  u_word flag = (read_reg(cpu, FL) & 0x0004u) ? 1 : 0;
  word offset = flag * (data - 2);
  write_reg(cpu, IP, current + offset);
}

void map_instructions(CPU* cpu){
  INSTRUCTION* ins = cpu->instructions;
  ins[0b0000000u] = &hlt;

  ins[0b0100000u] = &li0;
  ins[0b0100001u] = &li1;
  ins[0b0100010u] = &li2;
  ins[0b0100011u] = &li3;
  ins[0b0100100u] = &li4;
  ins[0b0100101u] = &li5;
  ins[0b0100110u] = &lia;

  ins[0b1000000u] = &ldb;
  ins[0b1000001u] = &ldw;
  ins[0b1000010u] = &stb;
  ins[0b1000011u] = &stw;
  ins[0b1000100u] = &psh;
  ins[0b1000101u] = &pop;

  ins[0b1100000u] = &cmp;
  ins[0b1100001u] = &not;
  ins[0b1100010u] = &orr;
  ins[0b1100011u] = &and;
  ins[0b1100100u] = &xor;
  ins[0b1100101u] = &add;
  ins[0b1100110u] = &sub;
  ins[0b1100111u] = &mul;
  ins[0b1101000u] = &div;
  ins[0b1101001u] = &lsl;
  ins[0b1101010u] = &lsr;

  ins[0b1110000u] = &jmp;
  ins[0b1110001u] = &jsr;
  ins[0b1110010u] = &beq;
  ins[0b1110011u] = &bgt;
  ins[0b1110100u] = &blt;
}
