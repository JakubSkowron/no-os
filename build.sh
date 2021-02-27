#/bin/bash

set -e

font=Uni2-TerminusBold28x14.psf
# You need a font in PSF format. Available for example in /usr/share/consolefonts/ in Ubuntu
if [[ ! -f ${font} ]]; then
  echo Font missing: ${font}
  exit 1
fi

toolchain=~/opt/cross/bin/
bootboot=~/opt/bootboot/dist
as=${toolchain}/x86_64-elf-as
ld=${toolchain}/x86_64-elf-ld
cc=${toolchain}/x86_64-elf-gcc


mkdir -p build
cd build

# Assemble and prepare font

cflags="-std=c17 -O2 -fpic -ffreestanding -fno-stack-protector -mno-red-zone -nostdlib -Wall --pedantic -I../include -I${bootboot}"
$as -o boot.o ../boot.s

# name of binary file is important, because it is a part of a symbol in .o file: _binary_*_start
ln -sf ../${font} font.psf
$ld --relocatable --format=binary -o font.o font.psf

# Link

$cc ${cflags} -T ../linker.ld -o os64.bin boot.o font.o ../kernel.c ../src/stdfun.c ../src/terminal.c

# Strip and read info

${toolchain}/x86_64-elf-strip --strip-all -K mmio -K fb -K bootboot -K environment -K initstack os64.bin
${toolchain}/x86_64-elf-readelf -hls os64.bin > os64.bin.txt

# Build ISO image

cd ..
./iso_image.sh
