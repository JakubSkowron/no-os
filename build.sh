#/bin/bash

set -e

toolchain=~/opt/cross/bin/
as=${toolchain}/i686-elf-as
cc=${toolchain}/i686-elf-gcc

mkdir -p build
cd build

# Assemble and Compile

cflags="-std=c17 -ffreestanding -O2 -Wall --pedantic -I../include"
$as -o boot.o ../boot.s
$cc ${cflags} -c ../kernel.c
$cc ${cflags} -c ../src/stdfun.c
$cc ${cflags} -c ../src/terminal.c

# Link

$cc -T ../linker.ld -o os.bin -ffreestanding -O2 -nostdlib boot.o kernel.o stdfun.o terminal.o
