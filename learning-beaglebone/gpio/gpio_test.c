#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpio.h"

/* 
 * By: Yusef Karim
 * This program allows you to choose a specified gpio pin as a input/output 
 * then allows you to write/read values to/from the pin.
 * Usage Example: ./gpio 49
 * Feel free to use this program in anyway you like, I am not responsible for
 * anything that breaks!
*/ 

int main(int argc, char* argv[])
{
    unsigned int gpio_number;
    char user_direction;

    // Convert and copy the passed argument for the gpio number
    sscanf(argv[1], "%d", &gpio_number);
    GpioExport(gpio_number);

    printf("\nEnter o for output or i for input for gpio%d: ", gpio_number);
    user_direction = getchar();

    if(user_direction == 'o') {
        int value;

        GpioDirection(gpio_number, user_direction);
        printf("\ngpio%d is now set as an output\n", gpio_number);
        while(1) {
            printf("Enter 1 or 0 to turn the gpio on/off, enter -1 to exit: ");
            scanf("%d", &value);
            
            if(value < -1 || value > 1) {
                printf("Invalid\n");
                continue;
            } else if (value == -1)
                break;
            else
                GpioSetValue(gpio_number, value);
        }
    } else if(user_direction == 'i') {
        char user_input;

        GpioDirection(gpio_number, user_direction);
        printf("\ngpio%d is now set as an input\n", gpio_number);
        while(1) {
            printf("Press Enter to read gpio%d\'s value, or q to quit: ", gpio_number);
            user_input = getchar();

            if(user_input == 'q')
                break;
            printf("\nValue is currently: %d\n", GpioGetValue(gpio_number));
        }
    } else {
        printf("Error, invalid direction!\n");
    }

    // Comment this out if you do not want the gpio pin to be unexported
    GpioUnexport(gpio_number);

    return 0;
}

