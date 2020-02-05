## About
A very basic 16-bit RISC processor simulation. Runs on boredom.</br>
</br>
Inspired by the Low Level JavaScript YouTube Channel: https://www.youtube.com/channel/UC56l7uZA209tlPTVOJiJ8Tw</br>

## The CPU
A very basic 16-bit RISC processor simulation written entirely in C11 without the use of a standard library. The CPU itself is little endian, and runs on little endian machines, but it is unknown if it will work properly on big endian machines. The "interface" that drives it does use the ANSI C standard library. The CPU instructions, and word-size can be easily modified. The CPU does NOT support instruction pipelining.

## Planned Updates
> Floating-point operations</br>
> Frame pointer</br>
> Memory-mapped I/O</br>
> Interrupts</br>
> More instructions</br>
> A more complex assembler</br>

## Reference
```
USER REGISTERS
AD = 0b000 RT = 0b001 R0 = 0b010 R1 = 0b011
R2 = 0b100 R3 = 0b101 R4 = 0b110 R5 = 0b111

R0-R6: General purpose registers
AD: Intended to store jump addresses
RT: Intended to store return addresses
SP: Stack pointer
FP: Frame pointer
IP: Instruction pointer
FL: Flag register

FORMATS
S-Type = [15...9][9..0]                = [OPCODE][EXTRA]
I-Type = [15...9][8...8][7...0]        = [OPCODE][EXTRA][IMMEDIATE]
M-Type = [15...9][8...6][5...0]        = [OPCODE][REGISTER][IMMEDIATE]
R-Type = [15...9][8...6][5...3][2...0] = [OPCODE][REGISTER][REGISTER][REGISTER]

INSTRUCTION SET
OPCODE  OP  INPUTS                 DESCRIPTION
0000000 hlt [NONE]               = stops the processor

0100000 ll0 [immv]               = load [immv] into a lower register R0, extra bit: 0
0100000 lu0 [immv]               = load [immv] into a upper register R0, extra bit: 1
0100001 ll1 [immv]               = load [immv] into a lower register R0, extra bit: 0
0100001 lu1 [immv]               = load [immv] into a upper register R0, extra bit: 1
0100010 ll2 [immv]               = load [immv] into a lower register R0, extra bit: 0
0100010 lu2 [immv]               = load [immv] into a upper register R0, extra bit: 1
0100011 ll3 [immv]               = load [immv] into a lower register R0, extra bit: 0
0100011 lu3 [immv]               = load [immv] into a upper register R0, extra bit: 1
0100100 ll4 [immv]               = load [immv] into a lower register R0, extra bit: 0
0100100 lu4 [immv]               = load [immv] into a upper register R0, extra bit: 1
0100101 ll5 [immv]               = load [immv] into a lower register R0, extra bit: 0
0100101 lu5 [immv]               = load [immv] into a upper register R0, extra bit: 1
0100110 lla [immv]               = load [immv] into a lower register AD, extra bit: 0
0100110 lua [immv]               = load [immv] into a upper register AD, extra bit: 1

1000000 ldb [reg2] [reg1] [reg0] = load byte at address [reg1] into [reg2]
1000001 ldw [reg2] [reg1] [reg0] = load word at address [reg1] into [reg2]
1000010 stb [reg2] [reg1] [reg0] = store byte at address [reg1] into [reg2]
1000011 stw [reg2] [reg1] [reg0] = store word at address [reg1] into [reg2]
1000100 psh [reg2] [reg1] [reg0] = push [reg2] onto top of the stack and SP += 2
1000101 pop [reg2] [reg1] [reg0] = pop stack and store top in [reg2] and SP -= 2

1100000 cmp [reg2] [reg1] [reg0] = compares [reg1] with [reg0] and sets register FL (signed)
1100001 not [reg2] [reg1] [reg0] = binary not [reg1] and stores result in [reg2]
1100010 orr [reg2] [reg1] [reg0] = binary or [reg1] and [reg0] and stores result in [reg2]
1100011 and [reg2] [reg1] [reg0] = binary and [reg1] and [reg0] and stores result in [reg2]
1100100 xor [reg2] [reg1] [reg0] = binary xor [reg1] and [reg0] and stores result in [reg2]
1100101 add [reg2] [reg1] [reg0] = add [reg1] to [reg0] and stores result in [reg2]
1100110 sub [reg2] [reg1] [reg0] = subtract [reg1] by [reg0] and stores result in [reg2]
1100111 mul [reg2] [reg1] [reg0] = multiply [reg1] by [reg0] and stores result in [reg2]
1101000 div [reg2] [reg1] [reg0] = divides [reg1] by [reg0] and stores result in [reg2]
1101001 lsl [reg2] [reg1] [reg0] = logical shift left [reg1] by [reg0] and stores results in [reg2]
1101010 lsr [reg2] [reg1] [reg0] = logical shift right [reg1] by [reg0] and stores results in [reg2]

1110000 jmp [reg2] [reg1] [reg0] = jumps by [reg2] (signed) amount
1110001 jsr [reg2] [reg1] [reg0] = jumps by [reg2] (signed) amount and sets RT = IP + 2
1110010 beq [reg2] [reg1] [reg0] = jumps by [reg2] (signed) amount based on FL register
1110011 bgt [reg2] [reg1] [reg0] = jumps by [reg2] (signed) amount based on FL register
1110100 blt [reg2] [reg1] [reg0] = jumps by [reg2] (signed) amount based on FL register
```
