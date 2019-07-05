#include <stdio.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <linux/i2c.h>
//#include <linux/i2c-dev.h>

typedef struct I2C_DEVICE {
    unsigned int bus;
    unsigned int device_id;
    int fd;
} I2C_DEVICE;

/* From Table 19. of the ADXL345 Data sheet */
enum ADXL345_ADDRESSES {
    DEVID          = 0x00,   // Device ID
    THRESH_TAP     = 0x1D,   // Tap Threshold
    OFSX           = 0x1E,   // X-axis Offset
    OFSY           = 0x1F,   // Y-axis Offset
    OFSZ           = 0x20,   // Z-axis Offset
    DUR            = 0x21,   // Tap duration
    LATENT         = 0x22,   // Tap latency
    WINDOW         = 0x23,   // Tap window
    THRESH_ACT     = 0x24,   // Activity threshold
    THRESH_INACT   = 0x25,   // Threshold inactivity
    TIME_INACT     = 0x26,   // Inactivity time
    ACT_INACT_CTL  = 0x27,   // Axis enable control for activity detection
    THRESH_FF      = 0x28,   // Free-fall threshold
    TIME_FF        = 0x29,   // Free-fall time
    TAP_AXES       = 0x2A,   // Axis control for single tap/double tap
    ACT_TAP_STATUS = 0x2B,   // Source of single tap/double tap
    BW_RATE        = 0x2C,   // Data rate and power mode control
    POWER_CTL      = 0x2D,   // Power-saving features control
    INT_ENABLE     = 0x2E,   // Interrupt enable control
    INT_MAP        = 0x2F,   // Interrupt mapping control
    INT_SOURCE     = 0x30,   // Source of interrupts
    DATA_FORMAT    = 0x31,   // Data format control
    DATAX0         = 0x32,   // X-axis Data 0
    DATAX1         = 0x33,   // X-axis Data 1
    DATAY0         = 0x34,   // Y-axis Data 0
    DATAY1         = 0x35,   // Y-axis Data 1
    DATAZ0         = 0x36,   // Z-axis Data 0
    DATAZ1         = 0x37,   // Z-axis Data 1
    FIFO_CTL       = 0x38,   // FIFO control
    FIFO_STATUS    = 0x39    // FIFO status
};


static short combine_registers(unsigned char msb, unsigned char lsb) {
    return ((short)msb<<8) | (short)lsb;
}


int main(void) {
    printf("%d", OFSX);
	return 0;
}
