#!/usr/bin/env bash

sed -f assembler/assembler.sed ${1} > ${2}
