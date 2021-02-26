#/bin/bash

set -e

toolchain=~/opt/cross/bin/
as=${toolchain}/i686-elf-as
cc=${toolchain}/i686-elf-gcc

# Assemble and Compile

cflags="-std=c17 -ffreestanding -O2 -Wall --pedantic -I."
$as -o boot.o boot.s
$cc ${cflags} -c -o kernel.o kernel.c
$cc ${cflags} -c -o standard_functions.o standard_functions.c

# Link

$cc -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o standard_functions.o
