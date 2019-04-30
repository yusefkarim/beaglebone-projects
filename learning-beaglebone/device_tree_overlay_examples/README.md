# Loading a custom Device Tree Overlay

Recent versions of the Linux kernel have depreceated the cape manager which was
the old way of loading capes. As of writing this, I am using Arch Linux with a Linux kernel version of 5.0.10. Below I describe the method I use to load my own device tree overlay file called *MY_OVERLAY.dts*.

First, I compile my overlay:
```
dtc -I dts -O dtb MY_OVERLAY.dts -o MY_OVERLAY.dtb
```

Then, I move it to a reliable location:
```
mv MY_OVERLAY.dtb /boot/dtbs/
cd /boot/
```

Next, I edit the boot.txt file and add my overlay file to be loaded:

**Note:** This is just a snippet of the file, I only add the line that starts
with *load*!
```
...
      fdt addr ${fdt_addr_r}
      load ${devtype} ${devnum}:${bootpart} 0x88060000 /boot/dtbs/MY_OVERLAY.dtb
      fdt resize ${filesize}
      fdt apply 0x88060000
...
```

Finally, I run the *mkscr* script then reboot:
```
./mkscr
reboot
```

# Other Notes

To compile a dtb file use the following command:

```
dtc -I dts -O dtb DTB_NAME.dts -o DTB_NAME.dtb
```

To decompile a dtb file use the following command:

```
dtc -I dtb -O dts DTB_NAME.dtb -o DTB_NAME.dts
```

The official beagleboard Github account has a repository with very well
documented overlays:

[https://github.com/beagleboard/bb.org-overlays]

