#!/bin/bash

# Make .iso image

target=os64.iso
source=build/os64.bin
isodir=iso_image
mkbootimg=~/opt/bootboot/mkbootimg

mkdir -p ${isodir}/boot/sys
cp ${source} ${isodir}/boot/sys/core
cp bootboot.cfg ${isodir}/boot/sys/config
cp bootboot.json ${isodir}

cd ${isodir}
$mkbootimg bootboot.json ${target}