# NOT TESTED AND NEEDS TO BE UPDATED

```
wget ftp://ftp.denx.de/pub/u-boot-2018.03.tar.bz2

tar -xjf u-boot-2018.03.tar.bz2

cd u-boot-2018.03

wget https://rcn-ee.com/repos/git/u-boot-patches/v2018.03/0001-am335x_evm-uEnv.txt-bootz-n-fixes.patch

patch -p1 < 0001-am335x_evm-uEnv.txt-bootz-n-fixes.patch

make am335x_boneblack_config

make

ls -l MLO u-boot.img
```
