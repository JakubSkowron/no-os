#!/bin/bash

# Make .iso image

target=os.iso
dir=iso_image

mkdir -p ${dir}/boot/grub
cp os.bin ${dir}/boot/
cp grub.cfg ${dir}/boot/grub

grub-mkrescue -o ${target} ${dir}