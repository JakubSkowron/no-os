# os - minimal kernel

## Build
You need a cross gcc and binutils: `--target=i686-elf`
```
./build.sh
```

More information: https://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build

## Make .iso image
You need `grub` and `xorriso`
```
./iso_image.sh
```

You can either use the resulting `.iso` image to boot a virtual machine (VirtualBox,...), or write to physical medium (USB,...) and boot on real hardware.

Needs BIOS (doesn't understand UEFI).

Use _Other/Unknown_ operating system setting in virtual machine.

Based on [this tutorial](https://wiki.osdev.org/C++_Bare_Bones) at wiki.osdev.org