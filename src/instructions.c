#include "instructions.h"

/* Special instructions */
static void hlt(CPU* cpu, const I_FORMAT* ins) {
  while(1);
}


/* Control instructions */
static void jpr(CPU* cpu, const I_FORMAT* ins) {
  u_word address = ins->r_type.reg2;
  write_reg(cpu, IP, address);
}

static void jps(CPU* cpu, const I_FORMAT* ins) {
  byte offset = ins->i_type.immv;
  CPU_REGISTER current = read_reg(cpu, IP);
  write_reg(cpu, AC, current);
  write_reg(cpu, IP, current + offset - 2);
}

static void jmp(CPU* cpu, const I_FORMAT* ins) {
  byte offset = ins->i_type.immv;
  u_word current = read_reg(cpu, IP);
  write_reg(cpu, IP, current + offset - 2);
}

static void beq(CPU* cpu, const I_FORMAT* ins) {
  u_byte flag = (read_reg(cpu, FL) & 0x0001) ? 1 : 0;
  u_word current = read_reg(cpu, IP);
  byte offset = flag * (ins->i_type.immv - 2);
  write_reg(cpu, IP, current + offset);
}

static void bgt(CPU* cpu, const I_FORMAT* ins) {
  u_byte flag = (read_reg(cpu, FL) & 0x0002) ? 1 : 0;
  u_word current = read_reg(cpu, IP);
  byte offset = flag * (ins->i_type.immv - 2);
  write_reg(cpu, IP, current + offset);
}

static void blt(CPU* cpu, const I_FORMAT* ins) {
  u_byte flag = (read_reg(cpu, FL) & 0x0004) ? 1 : 0;
  u_word current = read_reg(cpu, IP);
  byte offset = flag * (ins->i_type.immv - 2);
  write_reg(cpu, IP, current + offset);
}


/* Register management instrucions */
static void li0(CPU* cpu, const I_FORMAT* ins) {
  u_byte data = ins->i_type.immv;
  write_reg(cpu, R0, data);
}

static void li1(CPU* cpu, const I_FORMAT* ins) {
  u_byte data = ins->i_type.immv;
  write_reg(cpu, R1, data);
}

static void li2(CPU* cpu, const I_FORMAT* ins) {
  u_byte data = ins->i_type.immv;
  write_reg(cpu, R2, data);
}

static void li3(CPU* cpu, const I_FORMAT* ins) {
  u_byte data = ins->i_type.immv;
  write_reg(cpu, R3, data);
}

static void luh(CPU* cpu, const I_FORMAT* ins) {
  u_word upper = ins->i_type.immv;
  u_word current = read_reg(cpu, AC);
  current = (current & 0x00FF) | (upper << 8);
  write_reg(cpu, AC, current);
}

static void llh(CPU* cpu, const I_FORMAT* ins) {
  u_word upper = ins->i_type.immv;
  u_word current = read_reg(cpu, AC);
  current = (current & 0xFF00) | (upper << 0);
  write_reg(cpu, AC, current);
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


/* Arithmetic instrucions */
static void cmp(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->r_type.reg0;
  CPU_REGISTER reg1 = ins->r_type.reg1;
  u_word flag = read_reg(cpu, FL) & 0x0FF8;
  word data0 = read_reg(cpu, reg0);
  word data1 = read_reg(cpu, reg1);
  word results = data1 - data0;

  if(results == 0) {
    flag |= 0x0001;
  } else if(results > 0) {
    flag |= 0x0002;
  } else if(results < 0) {
    flag |= 0x0004;
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

static void asl(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->m_type.reg0;
  u_byte immv = ins->m_type.immv;
  u_word data = read_reg(cpu, reg0);
  write_reg(cpu, reg0, data << immv);
}

static void asr(CPU* cpu, const I_FORMAT* ins) {
  CPU_REGISTER reg0 = ins->m_type.reg0;
  u_byte immv = ins->m_type.immv;
  u_word data = read_reg(cpu, reg0);
  write_reg(cpu, reg0, data >> immv);
}

void map_instructions(CPU* cpu){
  INSTRUCTION* ins = cpu->instructions;
  ins[0b0000000] = &hlt;

  ins[0b0100000] = &jpr;
  ins[0b0100001] = &jps;
  ins[0b0100010] = &jmp;
  ins[0b0100011] = &beq;
  ins[0b0100100] = &bgt;
  ins[0b0100101] = &blt;

  ins[0b0110000] = &li0;
  ins[0b0110001] = &li1;
  ins[0b0110010] = &li2;
  ins[0b0110011] = &li3;
  ins[0b0110100] = &luh;
  ins[0b0110101] = &llh;

  ins[0b1000000] = &ldb;
  ins[0b1000001] = &ldw;
  ins[0b1000010] = &stb;
  ins[0b1000011] = &stw;

  ins[0b1100000] = &cmp;
  ins[0b1100001] = &not;
  ins[0b1100010] = &orr;
  ins[0b1100011] = &and;
  ins[0b1100100] = &xor;
  ins[0b1100101] = &add;
  ins[0b1100110] = &sub;
  ins[0b1100111] = &mul;
  ins[0b1101000] = &div;
  ins[0b1101001] = &asl;
  ins[0b1101010] = &asr;
}
