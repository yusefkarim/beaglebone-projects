#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This program will change the onboard usr3 LED to on, off, or flashing


#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void write_LED(char filename[], char value[]);
void remove_trigger();

int main(int argc, char* argv[])
{
    //If invalid arguments passed
    if(argc != 2)
    {
        printf("You goof, use this properly! Arguments are:\n");
        printf("1. on\n2. off\n3. flash\n4. status\n");
        printf("Ex. user_LED on\n");
        return 2;
    }

    printf("Starting the user_LED program!\n");
    printf("The current LED path is: " LED3_PATH "\n");

    //These if statements are checking which correct argument was passed
    //strcmp, compares two strings passed to it and returns 0 if the same
    if(strcmp(argv[1], "on") == 0)
    {
        printf("Turning the LED on.\n");
        remove_trigger();
        write_LED("/brightness", "1");
    }
    else if(strcmp(argv[1], "off") == 0)
    {
        printf("Turning the LED off.\n");
        remove_trigger();
        write_LED("/brightness", "0");
    }
    else if(strcmp(argv[1], "flash") == 0)
    {
        printf("Flashing the LED.");
        remove_trigger();
        write_LED("/trigger", "timer");
        write_LED("/delay_on", "50");
        write_LED("/delay_off", "50");
    }
    else if(strcmp(argv[1], "status") == 0)
    {
        FILE* fp; //creates a file pointer, fp
        char full_file_name[100];
        char line[80];
        //sends formatted output(second argument) as a string to full_file_name
        sprintf(full_file_name, LED3_PATH "/trigger");
        //Opens the file passing rt as the mode(read file)
        fp = fopen(full_file_name, "rt");
        //While not at end of file, keep er goin
        while(fgets(line, 80, fp) != NULL)
        {
            printf("%s", line);
        }
        fclose(fp);
    }
    else //Invalid argument passed
    {
        printf("You idiot! Pass a valid argument.\n");
    }

    printf("All done!\n");
    return 0;
}


void write_LED(char filename[], char value[])
{
    FILE* fp;   //file pointer, fp
    char full_file_name[100];   //string to store file path and filename
    sprintf(full_file_name, LED3_PATH "%s", filename);  //write file path/name
    fp = fopen(full_file_name, "w+");   //open the file for writing
    fprintf(fp, "%s", value);   //send the value to the file
    fclose(fp); //close the file using the file pointer
}

//Calls above function to set trigger value to none
void remove_trigger()
{
    write_LED("/trigger", "none");
}
