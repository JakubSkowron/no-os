#!/bin/bash

# Make .iso image

target=os.iso
source=build/os.bin
isodir=build/iso_image

mkdir -p ${isodir}/boot/grub
cp ${source} ${isodir}/boot/
cp grub.cfg ${isodir}/boot/grub

grub-mkrescue -o ${target} ${isodir}