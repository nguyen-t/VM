#!/usr/bin/env bash

sed -E -f assembler/pre.sed ${1} \
  | sed -E -f assembler/assembler.sed \
  | sed -E -f assembler/post.sed > ${2}
