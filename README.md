# os - minimal kernel

## Build
You need a cross gcc and binutils: `--target=x86_64-elf`, and a [BOOTBOOT dist](https://gitlab.com/bztsrc/bootboot/-/tree/master/dist)
```
./build.sh
```

More information: https://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build

## Make .iso image
You need `mkbootimg`
```
./iso_image.sh
```

You can either use the resulting `.iso` image to boot a virtual machine (VirtualBox,...), or write to physical medium (USB,...) and boot on real hardware.

Use _Other/Unknown_ operating system setting in virtual machine.

## BOOTBOOT
This kernel uses [BOOTBOOT](https://gitlab.com/bztsrc/bootboot) as a bootloader. It supports x86_64-efi.
For more information and example kernel implementations see [BOOTBOOT Example Kernels](https://gitlab.com/bztsrc/bootboot/-/tree/master/mykernel)

Specification: https://gitlab.com/bztsrc/bootboot/-/blob/master/bootboot_spec_1st_ed.pdf

## wiki.osdev.org
Many useful tutorials and informations at https://wiki.osdev.org/