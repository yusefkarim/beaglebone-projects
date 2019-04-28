#include <stdio.h>
#include <stdlib.h>

//BEFORE USING THIS LIBRARY YOU MUST ENABLE THE PWM DEVICE TREE OVERLAY OR THE
//DIRECTORY YOU NEED TO ACCESS WILL NOT EXIST

#define MAX_SIZE 200
#define PWM_PATH "/sys/class/pwm/pwmchip0"

void PWMSetup()
{
    FILE* fp;
    char *full_file_path = "/sys/devices/platform/bone_capemgr/slots";

    fp = fopen(full_file_path, "w");
    fprintf(fp, "BB-PWM1");
    fclose(fp);

}

void PWMExport(int pwm_num)
{
    char full_file_path[MAX_SIZE];
    FILE* fp;

    //Check if pin number for P9 header is 14 or 16
    if(pwm_num == 14)
        pwm_num = 0;        //Export number for EHRPWM1A
    else if(pwm_num == 16)
        pwm_num = 1;        //Export number for EHRPPWM1B
    else
    {
        printf("Error: invalid pin\n");
        exit(1);
    }

    sprintf(full_file_path, PWM_PATH "/export");    //Create the full file path
    fp = fopen(full_file_path, "w");                //Open export file for writing
    fprintf(fp, "%d", pwm_num);                     //Write pwm_num
    fclose(fp);                                     //Close file
}

void PWMDutyCycle(int pwm_num, int duty_cycle)
{
    char full_file_path[MAX_SIZE];
    FILE* fp;

    //Check if pin number for P9 header is 14 or 16
    if(pwm_num == 14)
    {
        pwm_num = 0;        //Export number for EHRPWM1A
        //Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:0/duty_cycle");
    }
    else if(pwm_num == 16)
    {
        pwm_num = 1;        //Export number for EHRPPWM1B
        //Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:1/duty_cycle");
    }
    else
    {
        printf("Error: invalid pin\n");
        exit(1);
    }

    fp = fopen(full_file_path, "w");                //Open export file for writing
    fprintf(fp, "%d", duty_cycle);                  //Write duty_cycle
    fclose(fp);                                     //Close file
}

void PWMPeriod(int pwm_num, int period)
{
    char full_file_path[MAX_SIZE];
    FILE* fp;

    //Check if pin number for P9 header is 14 or 16
    if(pwm_num == 14)
    {
        pwm_num = 0;        //Export number for EHRPWM1A
        //Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:0/period");
    }
    else if(pwm_num == 16)
    {
        pwm_num = 1;        //Export number for EHRPPWM1B
        //Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:1/period");
    }
    else
    {
        printf("Error: invalid pin\n");
        exit(1);
    }

    fp = fopen(full_file_path, "w");                //Open export file for writing
    fprintf(fp, "%d", period);                  //Write duty_cycle
    fclose(fp);                                     //Close file
}

void PWMEnable(int pwm_num, int enable)
{
    char full_file_path[MAX_SIZE];
    FILE* fp;

    if(enable != 0 || enable != 1)
    {
        printf("Error: enable value can only be 0 or 1\n");
        exit(1);
    }
    //Check if pin number for P9 header is 14 or 16
    if(pwm_num == 14)
    {
        pwm_num = 0;        //Export number for EHRPWM1A
        //Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:0/enable");
    }
    else if(pwm_num == 16)
    {
        pwm_num = 1;        //Export number for EHRPPWM1B
        //Create the full file path
        sprintf(full_file_path, PWM_PATH "/pwm-0:1/enable");
    }
    else
    {
        printf("Error: invalid pin\n");
        exit(1);
    }

    fp = fopen(full_file_path, "w");            //Open export file for writing

    fprintf(fp, "%d", enable);                  //Write duty_cycle
    fclose(fp);                                 //Close file
}


