#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include "snes.h"


#define CLK 11
#define LAT 9
#define DAT 10

#define GPLEV0  13          //read data line
#define GPSET0  7           //write 1
#define GPCLR0  10          //clear 0

#define GPIO_BASE       0xFE200000

#define CLK_REG     0xFE003004

static unsigned *gpioPtr = (unsigned*) GPIO_BASE;

#define INP_GPIO(g) *(gpioPtr+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpioPtr+((g)/10)) |= (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpioPtr+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

void writeClock(int writeZero) {
    if(writeZero)
    {gpioPtr[GPCLR0] = 1 << CLK;}
    else
    {gpioPtr[GPSET0] = 1 << CLK;}
    
}

void writeLatch(int writeZero) {
    if(writeZero)
    {gpioPtr[GPCLR0] = 1 << LAT;}

    else
    {gpioPtr[GPSET0] = 1 << LAT;}
}


int readData() {
    //printf("hello");
    char *test = gpioPtr[GPLEV0];
    //printarts(test);
    return (gpioPtr[GPLEV0] >> DAT) & 1; 
    
}

void init_snes_lines() {

    INP_GPIO(CLK);
    OUT_GPIO(CLK);
    INP_GPIO(LAT);
    OUT_GPIO(LAT);
    INP_GPIO(DAT);

}

unsigned read_snes() {

    unsigned int buttons[16];

    writeClock(0);
    writeLatch(0);
    wait(12);
    writeLatch(1);
                
    for(unsigned int i = 0; i < 16; i++){

        wait(6);
        writeClock(1);
        wait(6);
        unsigned int x = readData();
        buttons[i] = x;
        writeClock(0);
    }
    
    unsigned int results = 0;
    
    for(int i = 0; i < 12; i++){
            results |= buttons[i] << (12 - i -1);
    }


    return results;
}

void wait(int waitTime) {
    unsigned *clo = (unsigned*) CLK_REG;
    unsigned c = *clo + waitTime; // micro Secs
    while (c > *clo);
}