#include "gpio.h"
#include "uart.h"
#include <stdbool.h>
#include <stdio.h> 

#define     CLK         11  //the clock line
#define     LAT         9   //the latch line
#define     DAT         10  //the data line

#define GPLEV0  13          //read data line
#define GPSET0  7           //write 1
#define GPCLR0  10          //clear 0

#define GPIO_BASE   0xFE200000

#define CLO_REG     0x7E003004

bool buttonPressed = true;

unsigned int read_SNES();
void initSNES();
void printarts();
void wait();
void printarts();
void checkState(int* buttons);
bool printMessage();

static unsigned *gpioPtr = (unsigned*) GPIO_BASE;

#define INP_GPIO(g) *(gpioPtr+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpioPtr+((g)/10)) |= (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpioPtr+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

void snesStart() {
    initSNES();
    printarts("Please press a button\n");
    unsigned int * initbuttons;
    while(1)
    {
        initbuttons = read_SNES();
        checkState(initbuttons);
        if(printMessage(initbuttons)==false)
        {
            printarts("program is terminating...");
            return 0;

        };
    }
}

void checkState(int* buttons)
{
    int count = 0;
    for (int i = 0; i < 16; i++)
    {
        if (buttons[i] != 0)
        {
            count = count + 1;
        }
    }
    if(count == 16)
    {
        buttonPressed = false;
    }
}

void printarts(char *str) {
    uart_puts(str);
}

void initSNES()
{
    INP_GPIO(CLK);
    OUT_GPIO(CLK);
    INP_GPIO(LAT);
    OUT_GPIO(LAT);
    INP_GPIO(DAT);
}

unsigned int read_SNES()
{
    unsigned int *buttons = 0;
    writeClock(false);
    writeLatch(false);
    wait(12);
    writeLatch(true);
    for(int i=1; i <= 16; i++)
    {
        wait(6);
        writeClock(true);
        wait(6);
        buttons[i] = readData();
        writeClock(false);
    }
    return buttons;
}

void writeClock(bool writeZero) {
    if(writeZero)
    {gpioPtr[GPCLR0] = 1 << CLK;}
    else
    {gpioPtr[GPSET0] = 1 << CLK;}
    
}

void writeLatch(bool writeZero) {
    if(writeZero)
    {gpioPtr[GPCLR0] = 1 << LAT;}

    else
    {gpioPtr[GPSET0] = 1 << LAT;}
}

int readData() {
    //printf("hello");
    char *test = gpioPtr[GPLEV0];
    printarts(test);
    return (gpioPtr[GPLEV0] >> DAT) & 1; 
    
}

bool printMessage(int* buttons)
{   
    if((buttons[1] == 0) && buttonPressed == false)
    {
        printarts("You have pressed B\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[2] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Y\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[3] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Select\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[4] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Start\n");
        buttonPressed = true;
        wait(100000);
        return false;
    }
    if((buttons[5] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Joy-pad UP\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[6] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Joy-pad DOWN\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[7] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Joy-pad LEFT\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[8] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Joy-pad RIGHT\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[9] == 0) && buttonPressed == false)
    {
        printarts("You have pressed A\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[10] == 0) && buttonPressed == false)
    {
        printarts("You have pressed X\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[11] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Left\n");
        buttonPressed = true;
        wait(100000);
    }
    if((buttons[12] == 0) && buttonPressed == false)
    {
        printarts("You have pressed Right\n");
        buttonPressed = true;
        wait(100000);
    }
    return true;

}

void wait(int waitTime) {
    unsigned *clo = (unsigned*)CLO_REG;
    unsigned c = *clo + waitTime; // micro Secs
    while (c > *clo);
}