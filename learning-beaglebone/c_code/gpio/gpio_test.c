#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * By: Yusef Karim
 * This program allows you to choose a specified gpio pin as a input/output 
 * then allows you to write/read values to/from the pin.
 * Usage Example: ./gpio 49
 * Feel free to use this program in anyway you like, I am not responsible for
 * anything that breaks!
*/ 

#define GPIO_PATH "/sys/class/gpio"
#define MAX_SIZE 100

void GpioExport(unsigned int gpio_num);
void GpioUnexport(unsigned int gpio_num);
void GpioDirection(unsigned int gpio_num, char direction);
void GpioSetValue(unsigned int gpio_num, unsigned int value);
int GpioGetValue(unsigned int gpio_num);

int main(int argc, char* argv[])
{
    unsigned int gpio_number;
    char user_direction;

    //Convert and copy the passed argument for the gpio number
    sscanf(argv[1], "%d", &gpio_number);
    GpioExport(gpio_number);

    printf("\nEnter o for output or i for input for gpio%d: ", gpio_number);
    user_direction = getchar();

    if(user_direction == 'o')
    {
        int value;

        GpioDirection(gpio_number, user_direction);
        printf("\ngpio%d is now set as an output\n", gpio_number);
        while(1)
        {
            printf("Enter 1 or 0 to turn the gpio on/off, enter -1 to exit: ");
            scanf("%d", &value);
            
            if(value < -1 || value > 1)
            {
                printf("Invalid\n");
                continue;
            }
            if(value == -1)
                break;

            GpioSetValue(gpio_number, value);
        }
    }
    else if(user_direction == 'i')
    {
        char user_input;

        GpioDirection(gpio_number, user_direction);
        printf("\ngpio%d is now set as an input\n", gpio_number);
        while(1)
        {
            printf("Press Enter to read gpio%d\'s value, or q to quit: ", gpio_number);
            user_input = getchar();

            if(user_input == 'q')
                break;
            printf("\nValue is currently: %d\n", GpioGetValue(gpio_number));
        }
    }
    else
    {
        printf("Error, invalid direction!\n");
    }

    //Comment this out if you do not want the gpio pin to be unexported
    GpioUnexport(gpio_number);

    return 0;
}

//Exports the specified gpio pin so that it can be used
void GpioExport(unsigned int gpio_num)
{
    //File pointer
    FILE* fp;
    //String to store the entire file path
    char full_file_path[MAX_SIZE];
    //Create the full file path
    sprintf(full_file_path, GPIO_PATH "/export");

    //Open the export file for writing ONLY
    fp = fopen(full_file_path, "w");
    //Write the passed gpio number to export 
    fprintf(fp, "%d", gpio_num);
    //Close the file
    fclose(fp);
}

//Unexports the pin from the system
void GpioUnexport(unsigned int gpio_num)
{
    FILE* fp;
    char full_file_path[MAX_SIZE];

    sprintf(full_file_path, GPIO_PATH "/unexport");

    //Open the unexport file for writing ONLY
    fp = fopen(full_file_path, "w");
    //Write the passed gpio number to unexport 
    fprintf(fp, "%d", gpio_num);

    fclose(fp);
}

//Sets the gpio as output(o) or input(i)
void GpioDirection(unsigned int gpio_num, char direction)
{
    FILE* fp;
    char full_file_path[MAX_SIZE];

    sprintf(full_file_path, GPIO_PATH "/gpio%d/direction", gpio_num);

    //Open the direction file for writing ONLY
    fp = fopen(full_file_path, "w");

    //Write "in" if i pressed or "out" if o pressed to GPIO_PATH/gpio%d/direction
    if(direction == 'o')
        fprintf(fp, "out");
    else
        fprintf(fp, "in");

    fclose(fp);
}

//For an output pin, sets the pin value (0 or 1)
void GpioSetValue(unsigned int gpio_num, unsigned int value)
{
    FILE* fp;
    char full_file_path[MAX_SIZE];

    sprintf(full_file_path, GPIO_PATH "/gpio%d/value", gpio_num);

    //Open the value file for writing ONLY
    fp = fopen(full_file_path, "w");

    //Write 0(off) if value passed is 0 else write 1(on) to GPIO_PATH/gpio%d/value
    if(value == 0)
        fprintf(fp, "0");
    else
        fprintf(fp, "1");

    fclose(fp);
}

//For an input pin, gets the pin value (0 or 1) and returns it
int GpioGetValue(unsigned int gpio_num)
{
    FILE* fp;
    char full_file_path[MAX_SIZE], value;

    sprintf(full_file_path, GPIO_PATH "/gpio%d/value", gpio_num);

    //Open the value file for reading ONLY
    fp = fopen(full_file_path, "r");
    //Seeks to the beginning of the file
    fseek(fp, SEEK_SET, 0);
    //Read ascii 48(off == 0) or 49(on == 1) from the file GPIO_PATH/gpio%d/value
    fread(&value, 1, 1, fp);
    fclose(fp);

    //Return 0 if ascii 0 is read else return 1
    if(value == 48)
        return 0;
    else
        return 1;
}
