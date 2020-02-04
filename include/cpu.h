#ifndef CPU_H
#define CPU_H

#ifndef NULL
#define NULL (void*) 0
#endif

#ifndef STACK
#define STACK 0xFFFEu
#endif

typedef signed char byte;
typedef signed short word;
typedef unsigned char u_byte;
typedef unsigned short u_word;
typedef enum cpu_register CPU_REGISTER;
typedef union i_format I_FORMAT;
typedef struct cpu CPU;
typedef void (*INSTRUCTION)(CPU*, const I_FORMAT*);

enum cpu_register {
  R0, R1, R2, // General purpose registers
  R3, R4, R5, // General purpose registers
  AD, RT, // Special purpose registers
  SP, FP, // Stack and frame registers, inaccessible
  IP, FL, // Special purpose registers, inaccessible
};

#ifdef BIG_ENDIAN
union i_format {
  u_word raw; // Raw binary representation

  /* Unused instruction format (opcode 0XXXXXX) */
  struct {
    u_word opcode: 7; // Bytes[9..15] = opcode
    u_word extra: 9; // Bytes[0..8] = unused
  } s_type;

  /* Immediate-type instruction format (opcode 0XXXXXX) */
  struct {
    u_word opcode: 7; // Bytes[9..15] = opcode
    u_word extra: 1; // Bytes[8..8] = register
    u_word immv: 8; // Bytes[0..7] = register
  } i_type;

  /* Mixed-type instruction (opcode 1XXXXXX) */
  struct {
    u_word opcode: 7; // Bytes[9..15] = opcode
    u_word reg0: 3; // Bytes[6..8] = register
    u_word immv: 6; // Bytes[0..5] = register
  } m_type;

  /* Register-type instruction format (opcode 1XXXXXX) */
  struct {
    u_word opcode: 7; // Bytes[9..15] = opcode
    u_word reg2: 3; // Bytes[6..8] = register
    u_word reg1: 3; // Bytes[3..5] = register
    u_word reg0: 3; // Bytes[0..2] = register
  } r_type;
};

#else
union i_format {
  u_word raw; // Raw binary representation

  /* Unused instruction format (opcode 0XXXXXX) */
  struct {
    u_word extra: 9; // Bytes[0..8] = unused
    u_word opcode: 7; // Bytes[9..15] = opcode
  } s_type;

  /* Immediate-type instruction format (opcode 0XXXXXX) */
  struct {
    u_word immv: 8; // Bytes[0..7] = register
    u_word extra: 1; // Bytes[8..8] = register
    u_word opcode: 7; // Bytes[9..15] = opcode
  } i_type;

  /* Mixed-type instruction (opcode 1XXXXXX) */
  struct {
    u_word immv: 6; // Bytes[0..5] = register
    u_word reg0: 3; // Bytes[6..8] = register
    u_word opcode: 7; // Bytes[9..15] = opcode
  } m_type;

  /* Register-type instruction format (opcode 1XXXXXX) */
  struct {
    u_word reg0: 3; // Bytes[0..2] = register
    u_word reg1: 3; // Bytes[3..5] = register
    u_word reg2: 3; // Bytes[6..8] = register
    u_word opcode: 7; // Bytes[9..15] = opcode
  } r_type;
};
#endif

struct cpu {
  u_byte address[65536];
  u_word registers[11];
  INSTRUCTION instructions[128];
};

/* Reset function */
void cpu_reset(CPU* cpu);
void boot(CPU* cpu, const u_word* code, const u_word length);

/* Register functions */
u_word read_reg(CPU* cpu, const CPU_REGISTER reg);
void write_reg(CPU* cpu, const CPU_REGISTER reg, const u_word value);

/* Memory functions */
u_word read_adr(CPU* cpu, const u_word address, const u_byte bytes);
void write_adr(CPU* cpu, const u_word address, const u_word data, const u_byte bytes);

/* CPU clock functions */
u_word fetch(CPU* cpu);
I_FORMAT decode(CPU* cpu, const u_word hex);
void execute(CPU* cpu, const I_FORMAT binary);
void tick(CPU* cpu);

#endif
