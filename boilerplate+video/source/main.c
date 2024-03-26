#include "gpio.h"
#include "uart.h"
#include "framebuffer.h"
#include <pthread.h>
#include "snes.h"

#include "images/starts.h"


int appStart = 0;
int paused = 0;
int quit = 0;

void printf(char *str) {
	uart_puts(str);
}

int main()
{
    init_framebuffer(); // You can use framebuffer, width, height and pitch variables available in framebuffer.h
    
    // Draw a (Green) pixel at coordinates (10,10)
    drawPixel(10,10,0xFF00FF00);
    drawPixel(11,11,0xFF00FF00);
    drawPixel(12,12,0xFF00FF00);
    drawPixel(11,13,0xFF00FF00);
    drawPixel(11,14,0xFF00FF00);
    drawPixel(11,15,0xFF00FF00);

    // Print a message to the UART.
    printf("we printed a green pixel on the screen!!\n");

    drawImage(starts.pixel_data, starts.width, starts.height, 100, 100);

    drawCheckerboard(20,20,32, 0x00800000, 0x08000000);

    snesStart();
    
    

    /*appStart = 1;
    pthread_t snesInput;
    pthread_t drawScreen;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int th = pthread_create(&snesInput, &attr, input, "1")

    return 0;*/
}
