# os - minimal kernel

## Build
You need a cross gcc and binutils: `--target=x86_64-elf`, and `bootboot.h` from [BOOTBOOT dist](https://gitlab.com/bztsrc/bootboot/-/tree/master/dist)

Get or download any `.psf` font and put path to it in `build.sh`. Fonts are vailable for example in /usr/share/consolefonts/ in Ubuntu.

```
./build.sh
```


More information on cross-compiler: https://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build

## Make .iso image
You need `mkbootimg` from [BOOTBOOT binaries](https://gitlab.com/bztsrc/bootboot/-/tree/binaries)
```
./iso_image.sh
```

You can either use the resulting `.iso` image to boot a virtual machine (VirtualBox, qemu-kvm, ...), or write to physical medium (USB, ...) and boot on real hardware.

### qemu
```
$ qemu-system-x86_64 -drive file=os64.iso,format=raw
```

### VirtualBox

Use _Other/Unknown (64-bit)_ operating system setting in VirtualBox.

### USB drive
```
# dd bs=4M if=os64.iso of=/dev/sd[??]
```
You need to disable "Secure Boot" to boot from this device.

# About BOOTBOOT
This kernel uses [BOOTBOOT](https://gitlab.com/bztsrc/bootboot) as a bootloader. It supports x86_64-efi.
For more information and example kernel implementations see [BOOTBOOT Example Kernels](https://gitlab.com/bztsrc/bootboot/-/tree/master/mykernel)

Specification: https://gitlab.com/bztsrc/bootboot/-/blob/master/bootboot_spec_1st_ed.pdf

## wiki.osdev.org
Many useful tutorials and informations at https://wiki.osdev.org/

## i686
There is also a version for i686 architecture using `grub` instead of `bootboot` in [i686 branch](https://github.com/JakubSkowron/os/tree/i686).
