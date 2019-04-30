#!/bin/bash

PINMUX_FILE="/sys/kernel/debug/pinctrl/44e10800*/pins"

if (( $EUID != 0 )); then
    echo "This needs to be run as root!"
    exit
fi

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 PIN_NUMBER"
    exit
fi

awk /"pin $1 "/ $PINMUX_FILE
