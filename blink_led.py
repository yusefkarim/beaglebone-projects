from GPIOLibrary import GPIOProcessor
import time

GP = GPIOProcessor()

try:
    Pin27 = GP.getPin27()
    Pin27.out()

    Pin29 = GP.getPin29()
    Pin29.input()	

    for i in range(0,20):
        pinValue = Pin29.getValue();
	
	if pinValue == 1:
	    Pin27.high()
        else:
            Pin27.low()
        time.sleep(1)

finally:
    GP.cleanup()
