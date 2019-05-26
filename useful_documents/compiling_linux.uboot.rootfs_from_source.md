Instructions on how to get a fully working but very basic Linux system on the Beaglebone Black
by cross-compiling everything from source. I will be working towards an environment like this:

```
~/bbb-linux/
├── boot
├── buildroot
├── cross
├── linux
├── mnt
├── rootfs.tar.gz
└── u-boot
```

```
cd
mkdir bbb-linux && cd bbb-linux
```

## 1. Get a cross-compiler for your system (likely x86_64). There are several places you can get these pre-built for you,

1. <https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads>
    
2. <https://archlinuxarm.org/wiki/Distcc_Cross-Compiling>
    
3. <https://releases.linaro.org/components/toolchain/binaries/>

I will be using the ones provided by the Arch Linux developers (2):
```
wget https://archlinuxarm.org/builder/xtools/x-tools7h.tar.xz
mkdir cross
bsdtar -xf  x-tools7h.tar.xz -C cross
```
Moving things around such that the hierarchy is as such:
```
cross/
├── arm-unknown-linux-gnueabihf
├── bin
├── include
├── lib
├── libexec
└── share
```

Then export to an environment variable for convenience:
```
export CROSS=/home/cuyler/bbb-linux/cross/bin/arm-unknown-linux-gnueabihf-
${CROSS}gcc --version
```

## 2. Compiling U-boot
```
cd ~/bbb-linux/
git clone git://git.denx.de/u-boot.git
cd u-boot
make ARCH=arm CROSS_COMPILE=$CROSS am335x_boneblack_vboot_defconfig
make ARCH=arm CROSS_COMPILE=$CROSS -j4
```

This will pop out a MLO and u-boot.img file in your current directory, copy them to the boot folder for now:
```
mkdir ../boot
cp MLO u-boot.img ../boot/
```

## 3. Compiling mainline Linux kernel
```
cd ~/bbb-linux/
git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
cd linux
sudo make ARCH=arm CROSS_COMPILE=$CROSS omap2plus_defconfig
sudo make ARCH=arm CROSS_COMPILE=$CROSS zImage dtbs LOADADDR=0x80008000 -j4
cp arch/arm/boot/zImage ../boot/

mkdir ../boot/dtbs
cp arch/arm/boot/dts/am335x-boneblack.dtb ../boot/dtbs/
cp arch/arm/boot/dts/am335x-bone.dtb ../boot/dtbs/
cd ../boot/
```

## 4. Make boot script

We now have the SPL, u-boot, and the Linux kernel, we can create a short boot script by copying the one
the Arch Linux team has already made that u-boot can read once it has been loaded,
add the following to the file boot.txt:

boot.txt
```
if test -n ${distro_bootpart}; then setenv bootpart ${distro_bootpart}; else setenv bootpart 1; fi
part uuid ${devtype} ${devnum}:${bootpart} uuid

setenv bootargs "console=tty0 console=${console} root=PARTUUID=${uuid} rw rootwait"

if load ${devtype} ${devnum}:${bootpart} ${kernel_addr_r} /boot/zImage; then
  gpio set 54
  echo fdt: ${fdtfile}
  if load ${devtype} ${devnum}:${bootpart} ${fdt_addr_r} /boot/dtbs/${fdtfile}; then
      fdt addr ${fdt_addr_r}
      fdt resize ${filesize}
      fdt apply 0x88060000
    gpio set 55
    if load ${devtype} ${devnum}:${bootpart} ${ramdisk_addr_r} /boot/initramfs-linux.img; then
      gpio set 56
      bootz ${kernel_addr_r} ${ramdisk_addr_r}:${filesize} ${fdt_addr_r};
    else  
      gpio set 56
      bootz ${kernel_addr_r} - ${fdt_addr_r};
    fi;   
  fi;     
fi
```

Then run:
```
mkimage -A arm -O linux -T script -C none -n "U-Boot boot script" -d boot.txt boot.scr
```

### 5. Use Buildroot to make the root file system
```
cd ~/bbb-linux/
git clone git://git.buildroot.net/buildroot
cd buildroot
```

Buildroot is very straightforward, just run:
```
make menuconfig
```
To setup what you want, making sure you give it the path to the toolchain we already downloaded
and choosing ARM (little endian) -> ELF -> cortex-A9 -> EABIhf -> NEON -> ARM as the target. Then run:
```
make
cp output/images/rootfs.tar.gz ../
```

For more information go to: <https://buildroot.org/docs.html>


## 6. Create the bootable SD card:
```
cd ~/bbb-linux/
mkdir mnt
dd if=/dev/zero of=/dev/sdX bs=1M count=8
fdisk /dev/sdX      # Create a single DOS partition by pressing: o -> n -> Enter -> Enter -> Enter -> Enter -> w
mkfs.ext4 /dev/sdX1
mount /dev/sdX1 mnt
bsdtar -xpf rootfs.tar.gz -C mnt
sync
cp -r boot mnt/
dd if=mnt/boot/MLO of=/dev/sdX count=1 seek=1 conv=notrunc bs=128k
dd if=mnt/boot/u-boot.img of=/dev/sdX count=2 seek=1 conv=notrunc bs=384k
umount mnt
sync
```

## Done!

Put microSD card into your Beaglebone and hold the button near the card down.
You will almost certainly need a USB to TTL converter to see if it actually worked.














