#ifndef PWM_H
#define PWM_H

// Exports the specified PWM pin so that it can be used
void PWMExport(int pwm_num);

// Unexports the pin from the system
void PWMUnexport(unsigned int pwm_num);

// Sets the period for the PWM
void PWMPeriod(int pwm_num, int period);

// Sets the duty cycle for the PWM pulses
void PWMDutyCycle(int pwm_num, int duty_cycle);

// Enables (enable = 1) or disables (enable = 0) the PWM pin
void PWMEnable(int pwm_num, int enable);

#endif
