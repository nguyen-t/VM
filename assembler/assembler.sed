s/#.*//;

s/hlt/0000000000000000/I;
s/ll0/01100000/I;
s/lu0/01100001/I;
s/ll1/01100010/I;
s/lu1/01100011/I;
s/ll2/01100100/I;
s/lu2/01100101/I;
s/ll3/01100110/I;
s/lu3/01100111/I;
s/ll4/01101000/I;
s/lu4/01101001/I;
s/ll5/01101010/I;
s/lu5/01101011/I;
s/lla/01101100/I;
s/lua/01101101/I;
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

s/$R0/000/I;
s/$R1/001/I;
s/$R2/010/I;
s/$R3/011/I;
s/$R4/100/I;
s/$R5/101/I;
s/$AD/110/I;
s/$RT/111/I;

s/ //;
s/  //;
