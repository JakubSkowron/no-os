# os - minimal kernel

## Build
You need a cross `gcc` and `binutils`: `--target=i686-elf`
```
./build.sh
```

More information: https://wiki.osdev.org/C++_Bare_Bones

## Make .iso image
You need `grub` and `xorriso`
```
./iso_image.sh
```

Then you can either use a virtual machine (VirtualBox,...), or write it to physical medium (USB,...) and boot on real hardware.

Needs BIOS (doesn't understand UEFI). Use _Other/Unknown_ operating system setting in virtual machine.