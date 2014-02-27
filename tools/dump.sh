#!/bin/bash

tmpname=`tempfile -p avrasm -s .elf`
avr-objcopy -I binary -B avr -O elf32-avr $1 $tmpname
avr-objdump -D $tmpname
rm $tmpname
