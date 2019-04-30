#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define GPIO_PATH "/sys/class/gpio"

void GpioExport(unsigned int gpio_num) {
    FILE* fp;
    char full_file_path[MAX_SIZE];

    // Create the full file path
    sprintf(full_file_path, GPIO_PATH "/export");
    // Open the export file for writing ONLY
    fp = fopen(full_file_path, "w");
    // Write the passed gpio number to export
    fprintf(fp, "%d", gpio_num);
    fclose(fp);
}

void GpioUnexport(unsigned int gpio_num) {
    FILE* fp;
    char full_file_path[MAX_SIZE];

    // Create the full file path
    sprintf(full_file_path, GPIO_PATH "/unexport");
    // Open the unexport file for writing ONLY
    fp = fopen(full_file_path, "w");
    // Write the passed gpio number to unexport
    fprintf(fp, "%d", gpio_num);
    fclose(fp);

}

void GpioDirection(unsigned int gpio_num, char direction) {
    FILE* fp;
    char full_file_path[MAX_SIZE];

    // Create the full file path
    sprintf(full_file_path, GPIO_PATH "/gpio%d/direction", gpio_num);
    // Open the direction file for writing ONLY
    fp = fopen(full_file_path, "w");

    //Write "in" or "out" to GPIO_PATH/gpio%d/direction
    if(direction == 'o')
        fprintf(fp, "out");
    else if(direction == 'i')
        fprintf(fp, "in");
    else {
        fprintf(stderr, "Direction value of '%c' invalid!", direction);
        exit(-1);
    }
    fclose(fp);
}

void GpioSetValue(unsigned int gpio_num, unsigned int value) {
    FILE* fp;
    char full_file_path[MAX_SIZE];

    // Create the full file path
    sprintf(full_file_path, GPIO_PATH "/gpio%d/value", gpio_num);
    // Open the value file for writing ONLY
    fp = fopen(full_file_path, "w");

    // Write 0 (off) or 1 (on) to GPIO_PATH/gpio%d/value
    if(value == 0)
        fprintf(fp, "0");
    else if(value == 1)
        fprintf(fp, "1");
    else {
        fprintf(stderr, "Value of %u invalid!", value);
        exit(-1);
    }
    fclose(fp);
}

int GpioGetValue(unsigned int gpio_num) {
    FILE* fp;
    char full_file_path[MAX_SIZE], value;

    // Create the full file path
    sprintf(full_file_path, GPIO_PATH "/gpio%d/value", gpio_num);
    // Open the value file for reading ONLY
    fp = fopen(full_file_path, "r");
    // Seeks to the beginning of the file
    fseek(fp, SEEK_SET, 0);
    // Read ascii 48(off == 0) or 49(on == 1) from the file GPIO_PATH/gpio%d/value
    fread(&value, 1, 1, fp);
    fclose(fp);

    // Return 0 if ascii 0 is read else return 1
    if(value == 48)
        return 0;
    else
        return 1;
}

