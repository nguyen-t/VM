## About
A very basic 16-bit RISC processor simulation. Runs on boredom.</br>
</br>
Inspired by the Low Level JavaScript YouTube Channel: https://www.youtube.com/channel/UC56l7uZA209tlPTVOJiJ8Tw</br>

## The CPU
A very basic 16-bit RISC processor simulation written entirely in C11 without the use of a standard library. The CPU itself is little endian, and runs on little endian machines, it is unknown if it will work properly on big endian machines. The "vm" that drives it does use the ANSI C standard library. The CPU instructions, and word-size can be easily modified. The CPU does NOT support instruction pipelining.

## Planned Functionality
> Stack</br>
> Floating-point operations</br>
> Big endian byte order compatibility
> Memory-mapped I/O</br>
> Interrupts</br>
> Protection for certain registers (e.g. IP)</br>
> More instructions</br>

## Reference
```
REGISTERS
IP = 0b000  FL = 0b001  SP = 0b010  AC = 0b011
R0 = 0b100  R1 = 0b101  R2 = 0b110  R3 = 0b111

FORMATS
S-Type = [15...9][9..0]                = [OPCODE][UNUSED]
I-Type = [15...9][8...8][7...0]        = [OPCODE][UNUSED][IMMEDIATE]
M-Type = [15...9][8...6][5...0]        = [OPCODE][REGISTER][IMMEDIATE]
R-Type = [15...9][8...6][5...3][2...0] = [OPCODE][REGISTER][REGISTER][REGISTER]

INSTRUCTION SET
OPCODE  OP  INPUTS                 DESCRIPTION
0000000 hlt [NONE]               = stops the processor

0100000 jpr [NONE]               = jumps to absolute address at register [AC]
0100001 jps [immv]               = sets register AC to IP + 2 and jumps to relative address [immv] (signed)
0100010 jmp [immv]               = jumps to relative address [immv] (signed)
0100011 beq [immv]               = jumps to relative address [immv] (signed) based on FL register
0100100 bgt [immv]               = jumps to relative address [immv] (signed) based on FL register
0100101 blt [immv]               = jumps to relative address [immv] (signed) based on FL register

0110000 li0 [immv]               = load [immv] into a register R0
0110001 li1 [immv]               = load [immv] into a register R1
0110010 li2 [immv]               = load [immv] into a register R2
0110011 li3 [immv]               = load [immv] into a register R3
0110100 luh [immv]               = load [immv] into upper-half into register AC
0110101 llh [immv]               = load [immv] into lower-half into register AC

1000000 ldb [reg2] [reg1] [reg0] = load byte at address [reg1] into [reg2]
1000001 ldw [reg2] [reg1] [reg0] = load word at address [reg1] into [reg2]
1000010 stb [reg2] [reg1] [reg0] = store byte at address [reg1] into [reg2]
1000011 stw [reg2] [reg1] [reg0] = store word at address [reg1] into [reg2]

1100000 cmp [reg2] [reg1] [reg0] = compares [reg1] with [reg0] and sets register FL (signed)
1100001 not [reg2] [reg1] [reg0] = binary not [reg1] and stores result in [reg2]
1100010 orr [reg2] [reg1] [reg0] = binary or [reg1] and [reg0] and stores result in [reg2]
1100011 and [reg2] [reg1] [reg0] = binary and [reg1] and [reg0] and stores result in [reg2]
1100100 xor [reg2] [reg1] [reg0] = binary xor [reg1] and [reg0] and stores result in [reg2]
1100101 add [reg2] [reg1] [reg0] = add [reg1] to [reg0] and stores result in [reg2]
1100110 sub [reg2] [reg1] [reg0] = subtract [reg1] by [reg0] and stores result in [reg2]
1100111 mul [reg2] [reg1] [reg0] = multiply [reg1] by [reg0] and stores result in [reg2]
1101000 div [reg2] [reg1] [reg0] = divides [reg1] by [reg0] and stores result in [reg2]
1101001 asl [reg2] [immv]        = arithmetic shift left [reg2] by [immv] bits
1101010 asr [reg2] [immv]        = arithmetic shift right [reg2] by [immv] bits
```