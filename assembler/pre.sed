# Clean up white-spaces and comments
s/#.*//;
s/^[ | ]*//g;
/^[[:space:]]*$/d;

# Expands pseudo-instructions
s/^(jmp|jsr|beq|bgt|blt)[[:space:]]+([0-1]{16})/lia \2\n\1 \$ad/I;
s/^(jmp|jsr|beq|bgt|blt)[[:space:]]+(0x[0-9a-f]{4})/lia \2\n\1 \$ad/I;
s/^li([0-5a])[[:space:]]+([0-1]{8})([0-1]{8})/ll\1 \3\nlu\1 \2/I;
s/^li([0-5a])[[:space:]]+0x([0-9a-f]{2})([0-9a-f]{2})/ll\1 0x\3\nlu\1 0x\2/I;
