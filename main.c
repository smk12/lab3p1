// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"
#include "config.h"
#include "interrupt.h"
#include "math.h"


volatile int temp;
volatile int ones;
volatile int tenths;
volatile int hundreds;
volatile int adcBuffer;
volatile float adcFloat;
volatile const float bufferSize = 1023.0;
volatile const float refVolt = 3.3;



int main(void)
{
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initLCD();
    initADC();
    initPWM();
    
    //adc1buff1
    while(1)
    {
        
        moveCursorLCD(0,0);
        if(IFS0bits.AD1IF==1)
        {
            adcBuffer = ADC1BUF0;
            IFS0bits.AD1IF = 0;
        }
        adcFloat = (adcBuffer/bufferSize)*refVolt;
        ones = (int)floor(adcFloat);
        tenths = (int)floor((adcFloat-ones)*10);
        hundreds = (int)floor(((adcFloat-ones)*10-tenths)*10);
        
        
        printCharLCD((char)ones+'0');
        printCharLCD('.');
        printCharLCD((char)tenths+'0');
        printCharLCD((char)hundreds+'0');
        /*
        for(temp=0;temp<=10;temp++)
            delayMs(200);
        */ 
    }
         

    return 0;
     
}

