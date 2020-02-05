#!/usr/bin/env bash

sed -E -f assembler/assembler.sed ${1} | sed -E -f assembler/hex.sed > ${2}
