#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>

/* Worse version of devmem2 for education purposes,
 * find the much better implementation of the original here:
 * https://github.com/radii/devmem2
 */

/* Example usage:
 *  The AM335x Technical Reference Manual tells us that there
 *  are registers that hold the value of the mac address for this device.
 *
 *  Using the base address of 0x44e10000 (page 180 of TRM):
 *  - mac_id0_lo register has offset 0x630
 *  - mac_id0_hi register has offset 0x634
 *
 *  To get your mac address, use:
 *  ./devmem 0x44e10630
 *  ./devmem 0x44e10634
 */

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

int main(int argc, char **argv) {
    int fd;
    void *map_base, *virt_addr;
    unsigned long read_result;
    off_t target;

    if(argc < 2) {
        printf("Usage: ./devmem 0xADDRESS\n");
        exit(1);
    }
    target = strtoul(argv[1], 0, 0);

    if((fd = open("/dev/mem", O_RDONLY | O_SYNC)) == -1) {
        perror("Error opening /dev/mem");
        exit(1);
    }

    map_base = mmap(0, MAP_SIZE, PROT_READ, MAP_PRIVATE, fd,
                    target & ~MAP_MASK);
    if(map_base == (void *) -1) {
        perror("mmap() error");
        exit(1);
    }

    virt_addr = map_base + (target & MAP_MASK);
    read_result = *((unsigned long *) virt_addr);
    printf("Value at address 0x%X (%p): 0x%X\n", target, virt_addr,
           read_result);

    munmap(map_base, MAP_SIZE);
    close(fd);
    return 0;
}

