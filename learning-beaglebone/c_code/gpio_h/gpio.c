#include <stdio.h>
//#include <stdlib.h>

#define MAX_SIZE 100
#define GPIO_PATH "/sys/class/gpio"

//Exports the specified gpio pin so that it can be used
void GpioExport(unsigned int gpio_num)
{
    FILE* fp;                           //File pointer
    char full_file_path[MAX_SIZE];      //String to store the entire file path

    //Create the full file path
    sprintf(full_file_path, GPIO_PATH "/export");

    fp = fopen(full_file_path, "w");    //Open the export file for writing ONLY
    fprintf(fp, "%d", gpio_num);        //Write the passed gpio number to export
    fclose(fp);                         //Close the file
}

//Unexports the pin from the system
void GpioUnexport(unsigned int gpio_num)
{
    FILE* fp;                           //File pointer
    char full_file_path[MAX_SIZE];      //String to store the entire file path

    //Create the full file path
    sprintf(full_file_path, GPIO_PATH "/unexport");

    fp = fopen(full_file_path, "w");    //Open the unexport file for writing ONLY
    fprintf(fp, "%d", gpio_num);        //Write the passed gpio number to unexport
    fclose(fp);                         //Close the file

}

//Sets the gpio as output(o) or input(i)
void GpioDirection(unsigned int gpio_num, char direction)
{
    FILE* fp;                           //File pointer
    char full_file_path[MAX_SIZE];      //String to store the entire file path

    //Create the full file path
    sprintf(full_file_path, GPIO_PATH "/gpio%d/direction", gpio_num);

    fp = fopen(full_file_path, "w");    //Open the direction file for writing ONLY

    //Write "in" if i pressed or "out" if o pressed to GPIO_PATH/gpio%d/direction
    if(direction == 'o')
        fprintf(fp, "out");
    else
        fprintf(fp, "in");

    fclose(fp);                         //Close the file
}

//For an output pin, sets the pin value (0 or 1)
void GpioSetValue(unsigned int gpio_num, unsigned int value)
{
    FILE* fp;                           //File pointer
    char full_file_path[MAX_SIZE];      //String to store the entire file path

    //Create the full file path
    sprintf(full_file_path, GPIO_PATH "/gpio%d/value", gpio_num);

    fp = fopen(full_file_path, "w");    //Open the value file for writing ONLY

    //Write 0(off) if value passed is 0 else write 1(on) to GPIO_PATH/gpio%d/value
    if(value == 0)
        fprintf(fp, "0");
    else
        fprintf(fp, "1");

    fclose(fp);                         //Close the file
}

//For an input pin, gets the pin value (0 or 1) and returns it
int GpioGetValue(unsigned int gpio_num)
{
    FILE* fp;                           //File pointer
    //String to store the entire file path, number to store current gpio value
    char full_file_path[MAX_SIZE], value;

    //Create the full file path
    sprintf(full_file_path, GPIO_PATH "/gpio%d/value", gpio_num);

    fp = fopen(full_file_path, "r");    //Open the value file for reading ONLY
    fseek(fp, SEEK_SET, 0);             //Seeks to the beginning of the file
    //Read ascii 48(off == 0) or 49(on == 1) from the file GPIO_PATH/gpio%d/value
    fread(&value, 1, 1, fp);
    fclose(fp);                         //Close the file

    //Return 0 if ascii 0 is read else return 1
    if(value == 48)
        return 0;
    else
        return 1;
}

