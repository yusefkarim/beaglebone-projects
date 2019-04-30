#!/bin/bash

#creates the gpio folder for gpio49
echo 49 > /sys/class/gpio/export
#Changes the gpio to an output pin
echo "out" > /sys/class/gpio/gpio49/direction

COUNTER=0
while [ $COUNTER -lt 100000 ]; do
    echo 0 > /sys/class/gpio/gpio49/value
    echo 1 > /sys/class/gpio/gpio49/value
    let COUNTER=COUNTER+1
done
#Gets rid of gpio folder for gpio49
echo 49 > /sys/class/gpio/unexport
