s/#.*//;

s/([(jmp)(jsr)(beq)(bgt)(blt)]) ([0-1]{16})/lia \2\n\1 \$ad/I
s/([(jmp)(jsr)(beq)(bgt)(blt)]) 0x([0-9a-f]{4})/lia 0x\2\n\1 \$ad/I
s/li([0-5a]) ([0-1]{8})([0-1]{8})/ll\1 \3\nlu\1 \2/I;
s/li([0-5a]) 0x([0-1a-f]{2})([0-1a-f]{2})/ll\1 0x\3\nlu\1 0x\2/I;

s/hlt/0000000/I;
s/ll0/01000000/I;
s/lu0/01000001/I;
s/ll1/01000010/I;
s/lu1/01000011/I;
s/ll2/01000100/I;
s/lu2/01000101/I;
s/ll3/01000110/I;
s/lu3/01000111/I;
s/ll4/01001000/I;
s/lu4/01001001/I;
s/ll5/01001010/I;
s/lu5/01001011/I;
s/lla/01001100/I;
s/lua/01001101/I;
s/ldb/1000000/I;
s/ldw/1000001/I;
s/stb/1000010/I;
s/stw/1000011/I;
s/psh/1000100/I;
s/pop/1000101/I;
s/cmp/1100000/I;
s/not/1100001/I;
s/orr/1100010/I;
s/and/1100011/I;
s/xor/1100100/I;
s/add/1100101/I;
s/sub/1100110/I;
s/mul/1100111/I;
s/div/1101000/I;
s/lsl/1101001/I;
s/lsr/1101010/I;
s/jmp/1110000/I;
s/jsr/1110001/I;
s/beq/1110010/I;
s/bgt/1110011/I;
s/blt/1110100/I;

s/\$r0/000/I;
s/\$r1/001/I;
s/\$r2/010/I;
s/\$r3/011/I;
s/\$r4/100/I;
s/\$r5/101/I;
s/\$ad/110/I;
s/\$rt/111/I;

s/ //g;
s/  //g;
/^[[:space:]]*$/d
s/^([0-1]{7})$/\1000000000/
s/^([0-1]{10})$/\1000000/
s/^([0-1]{13})$/\1000/
