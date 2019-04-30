#!/bin/bash

# Press ctrl-a-d to detach communications
# Press ctrl-a-\ to quit
clear

echo "Starting serial communications...."
sleep 1

#BaudRate=115,200, 8 data bits, no parity bits, 1 stop bit, ignore hang-ups
sudo screen /dev/ttyUSB0 115200,cs8,-parenb,-cstopb,-hupcl

