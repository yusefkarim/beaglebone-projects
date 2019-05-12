# General steps to configure Arch Linux for the Beaglebone Black

# -----------Creating the SD Card-----------

Zero out SD card: 
```
dd if=/dev/zero of=/dev/sdc bs=1M count=8
```

Partition SD card:

If there are already partitions, make sure they are unmounted
```
umount /dev/sdc1
```

Start fdisk
```
fdisk /dev/sdc
```

At the fdisk prompt, delete old partitions and create a new one:
Type o. This will clear out any partitions on the drive.
Type p to list partitions. There should be no partitions left.
Now type n, then p for primary, 1 for the first partition on the drive, 2048 for the first sector, and then press ENTER to accept the default last sector.
Write the partition table and exit by typing w.

Create the ext4 filesystem:
```
mkfs.ext4 /dev/sdc1
```

Mount and extract root filesystem
```
mkdir mnt
mount /dev/sdc1 mnt
wget http://os.archlinuxarm.org/os/ArchLinuxARM-am33x-latest.tar.gz
bsdtar -xpf ArchLinuxARM-am33x-latest.tar.gz -C mnt && sync
```

Copy U-Boot to the SD card:
    * Secondary Program Loader (MLO) goes at address 0x20000 (128 KiB)
    * Second Stage Bootloader/U-Boot (u-boot.img) goes at 0x60000 (384 KiB)
```
dd if=mnt/boot/MLO of=/dev/sdc count=1 seek=1 conv=notrunc bs=128k
dd if=mnt/boot/u-boot.img of=/dev/sdc count=2 seek=1 conv=notrunc bs=384k
umount mnt
sync
```

# -----------Booting Arch Linux on the Beaglebone-----------

Insert the SD card into the BeagleBone, connect ethernet, and apply 5V power.
Make sure to hold the boot button near the micro sd slot down while powering the board. Use ssh or serial adaptor to get terminal.

# -----------Setting up Arch Linux on the Beaglebone eMMC-----------

```
dd if=/dev/zero of=/dev/mmcblk1 bs=1M count=8
fdisk /dev/mmcblk1
umount /dev/mmcblk1p1
mkfs.ext4 /dev/mmcblk1p1
mkdir mnt
mount /dev/mmcblk1p1 mnt
# Download the latest image again or just copy from your computer
wget http://os.archlinuxarm.org/os/ArchLinuxARM-am33x-latest.tar.gz
bsdtar -xpf ArchLinuxARM-am33x-latest.tar.gz -C mnt
sync
dd if=mnt/boot/MLO of=/dev/mmcblk1 count=1 seek=1 conv=notrunc bs=128k
dd if=mnt/boot/u-boot.img of=/dev/mmcblk1 count=2 seek=1 conv=notrunc bs=384k
umount mnt
sync
```
Power down the system, waiting until all the LEDs go out:
Remove power, remove the micro SD card, then reapply power.

# -----------Post-Installation stuff-----------

Set your beaglebone's language and locale, this example will use en\_US.UTF-8
```
vi /etc/locale.gen
locale-gen
echo LANG=en_US.UTF-8 > /etc/locale.conf
export LANG=en_US.UTF-8
```

Identify your time zone and set it permanently
```
ls /usr/share/zoneinfo/Canada
ln -sf /usr/share/zoneinfo/Canada/Central /etc/localtime
hwclock --systohc --utc
```

Change beaglebone hostname
```
# Change alarm to your hostname
vi /etc/hostname
# Also add your host name to /etc/hosts, add this line
127.0.1.1	HOSTNAME.localdomain	HOSTNAME
```

Change alarm user username
```
usermod -l surt alarm
usermod -d /home/surt -m surt
```

Update and install some packages
```
pacman -Syu
pacman -S base-devel vim git
```
Change default runlevel for systemd to be non-graphical
```
systemctl set-default multi-user.target
```

Setting up wifi. I am using the tp-link TL-WN725N which wpa_supplicant does not support with it's new drivers but does with the old *wext*, this requires a little bit of messing around to get working.

First enable dhcpcd and create wpa\_supplicant config file and enable its service:
```
systemctl enable dhcpcd
wpa_passphrase $SSID $PASSWORD > /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
systemctl enable wpa_supplicant@wlan0
```

Next, we have to change the systemd service script to try the old wext drivers if n180211 doesn't work:

**WARNING:** If you update the wpa\_supplicant package this file will be
overwritten and you won't have WIFI! You can make a bootup script to run the
command shown below if you want to avoid this.
```
vim /usr/lib/systemd/system/wpa_supplicant\@.service

# Find the following line:
ExecStart=/usr/bin/wpa_supplicant -c/etc/wpa_supplicant/wpa_supplicant-%I.conf -i%I

# And change it to
ExecStart=/usr/bin/wpa_supplicant -c/etc/wpa_supplicant/wpa_supplicant-%I.conf -Dnl80211,wext -i%I
```
