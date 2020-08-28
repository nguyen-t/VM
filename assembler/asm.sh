#!/usr/bin/env bash

# Converts it into big endian machine code
# Big endian to little endian conversion is done in boot()
sed -E -f assembler/pre.sed ${1} \
  | sed -E -f assembler/assembler.sed \
  | sed -E -f assembler/post.sed > ${2}
