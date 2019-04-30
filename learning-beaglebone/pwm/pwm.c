#include <stdio.h>
#include <stdlib.h>

// BEFORE USING THIS LIBRARY YOU MUST ENABLE THE PWM DEVICE TREE OVERLAY
// OTHERWISE THE DIRECTORY YOU NEED TO ACCESS WILL NOT EXIST

#define MAX_SIZE 200
#define PWM_PATH "/sys/class/pwm/pwmchip0"

void PWMExport(int pwm_num) {
    char full_file_path[MAX_SIZE];
    FILE* fp;

    // Check if pin number for P9 header is 14 or 16
    // Export number for EHRPWM1A (P9_14) or EHRPPWM1B (P9_16)
    if(pwm_num == 14)
        pwm_num = 0;
    else if(pwm_num == 16)
        pwm_num = 1;
    else {
        printf("Error: invalid pin\n");
        exit(1);
    }

    // Create the full file path
    sprintf(full_file_path, PWM_PATH "/export");
    // Open export file for writing
    fp = fopen(full_file_path, "w");
    // Write pwm_num to PWM_PATH/export
    fprintf(fp, "%d", pwm_num);
    fclose(fp);
}

void PWMUnexport(int pwm_num) {
    char full_file_path[MAX_SIZE];
    FILE* fp;

    // Check if pin number for P9 header is 14 or 16
    // Export number for EHRPWM1A (P9_14) or EHRPPWM1B (P9_16)
    if(pwm_num == 14)
        pwm_num = 0;
    else if(pwm_num == 16)
        pwm_num = 1;
    else {
        printf("Error: invalid pin\n");
        exit(1);
    }

    // Create the full file path
    sprintf(full_file_path, PWM_PATH "/unexport");
    // Open export file for writing
    fp = fopen(full_file_path, "w");
    // Write pwm_num to PWM_PATH/export
    fprintf(fp, "%d", pwm_num);
    fclose(fp);
}

void PWMPeriod(int pwm_num, int period) {
    char full_file_path[MAX_SIZE];
    FILE *fp;

    // Check if pin number for P9 header is 14 or 16
    // Export number for EHRPWM1A (P9_14) or EHRPPWM1B (P9_16)
    if(pwm_num == 14) {
        // Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:0/period");
    } else if(pwm_num == 16) {
        // Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:1/period");
    } else {
        printf("Error: invalid pin\n");
        exit(1);
    }

    // Open period file for writing
    fp = fopen(full_file_path, "w");
    // Write period for specified PWM pin
    fprintf(fp, "%d", period);
    fclose(fp);
}

void PWMDutyCycle(int pwm_num, int duty_cycle) {
    char full_file_path[MAX_SIZE];
    FILE* fp;

    // Check if pin number for P9 header is 14 or 16
    // Export number for EHRPWM1A (P9_14) or EHRPPWM1B (P9_16)
    if(pwm_num == 14) {
        // Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:0/duty_cycle");
    } else if(pwm_num == 16) {
        // Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:1/duty_cycle");
    } else {
        printf("Error: invalid pin\n");
        exit(1);
    }

    // Open duty_cycle file for writing
    fp = fopen(full_file_path, "w");
    // Write duty_cycle for specified PWM pin
    fprintf(fp, "%d", duty_cycle);
    fclose(fp);
}

void PWMEnable(int pwm_num, int enable) {
    char full_file_path[MAX_SIZE];
    FILE* fp;

    if(enable < 0 || enable > 1) {
        printf("Error: enable value can only be 0 or 1\n");
        exit(1);
    }

    // Check if pin number for P9 header is 14 or 16
    // Export number for EHRPWM1A (P9_14) or EHRPPWM1B (P9_16)
    if(pwm_num == 14) {
        // Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:0/enable");
    } else if(pwm_num == 16) {
        // Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:1/enable");
    } else {
        printf("Error: invalid pin\n");
        exit(1);
    }

    // Open enable file for writing
    fp = fopen(full_file_path, "w");
    // Write enable value for specified PWM pin
    fprintf(fp, "%d", enable);
    fclose(fp);
}

