#include <stdio.h>
#include <unistd.h>
#include "pwm.h"

int main(int argc, char* argv[]) {
    unsigned int pwm_number;

    sscanf(argv[1], "%d", &pwm_number);

    PWMExport(pwm_number);

    PWMPeriod(pwm_number, 20000000);
    PWMEnable(pwm_number, 1);
    PWMDutyCycle(pwm_number, 570000);
    sleep(1);
    PWMDutyCycle(pwm_number, 1460000);
    sleep(1);
    PWMDutyCycle(pwm_number, 2350000);
    sleep(1);
    PWMDutyCycle(pwm_number, 1460000);
    sleep(1);
    PWMEnable(pwm_number, 0);

    PWMUnexport(pwm_number);

    return 0;
}
