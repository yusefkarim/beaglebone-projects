#ifndef GPIO_H
#define GPIO_H

// Exports the specified gpio pin so that it can be used
void GpioExport(unsigned int gpio_num);

// Unexports the pin from the system
void GpioUnexport(unsigned int gpio_num);

// Sets the gpio as output ('o') or input ('i')
void GpioDirection(unsigned int gpio_num, char direction);

// For an output pin, sets the pin value (0 or 1)
void GpioSetValue(unsigned int gpio_num, unsigned int value);

// For an input pin, gets the pin value (0 or 1) and returns it
int GpioGetValue(unsigned int gpio_num);

#endif
