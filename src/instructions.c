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
  ins[0x00u] = &hlt; // 0000000

  ins[0x10u] = &li0; // 0010000
  ins[0x11u] = &li1; // 0010001
  ins[0x12u] = &li2; // 0010010
  ins[0x13u] = &li3; // 0010011
  ins[0x14u] = &li4; // 0010100
  ins[0x15u] = &li5; // 0010101
  ins[0x16u] = &lia; // 0010110

  ins[0x20u] = &ldb; // 0100000
  ins[0x21u] = &ldw; // 0100001
  ins[0x22u] = &stb; // 0100010
  ins[0x23u] = &stw; // 0100011
  ins[0x24u] = &psh; // 0100100
  ins[0x25u] = &pop; // 0100101

  ins[0x30u] = &cmp; // 0110000
  ins[0x31u] = &not; // 0110001
  ins[0x32u] = &orr; // 0110010
  ins[0x33u] = &and; // 0110011
  ins[0x34u] = &xor; // 0110100
  ins[0x35u] = &add; // 0110101
  ins[0x36u] = &sub; // 0110110
  ins[0x37u] = &mul; // 0110111
  ins[0x38u] = &div; // 0111000
  ins[0x39u] = &lsl; // 0111001
  ins[0x3Au] = &lsr; // 0111010

  ins[0x40u] = &jmp; // 1000000
  ins[0x41u] = &jsr; // 1000001
  ins[0x42u] = &beq; // 1000010
  ins[0x43u] = &bgt; // 1000011
  ins[0x44u] = &blt; // 1000100
}
