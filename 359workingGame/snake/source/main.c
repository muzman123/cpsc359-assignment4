
#include "gpio.h"
#include "uart.h"
#include "snes.h"
#include "framebuffer.h"
#include "level.h"
//#include "myheader.h"
//#include "images/lev1.h"
#include "images/snake.h"
#include "images/tile.h"
#include "images/starts.h"
#include "images/arrow.h"
#include "images/antipointer.h"
#define GPIO_BASE 0xFE200000

int gameStart = 0;

void printf(char *str) {
	uart_puts(str);
}

int main(){
	init_snes_lines();
    init_framebuffer(); // You can use framebuffer, width, height and pitch variables available in framebuffer.h
    printf("bruv");
	unsigned int *game_start = (unsigned int *) CLK_REG;
	unsigned int game_end = *game_start +(120 * 1000000);

    gameStage.lives = 4;
    gameStage.currentLevel = 0;
	gameStage.s.isShielded = 0;
	gameStage.s.posx = 4;
	gameStage.s.posy = 4;

    fillScreen(0x00000000);

    int pointerx = 200;
    int pointery = 320;
    drawImage(starts.pixel_data,starts.width,starts.height,1,1);
    drawImage(arrow.pixel_data, arrow.width,arrow.height,pointerx,pointery);
	unsigned int input = read_snes();

		while(!gameStart) {
			input = read_snes();
			printf("bruv");
			if(input == DOWN && pointery == 320)
			{
				printf("up");
				drawImage(antipointer.pixel_data,antipointer.width,antipointer.height,pointerx,pointery);
				pointery += 100;
				drawImage(arrow.pixel_data,arrow.width,arrow.height,pointerx,pointery);
			}

			if(input == UP && pointery == 420)
			{
				printf("down");
				drawImage(antipointer.pixel_data,antipointer.width,antipointer.height,pointerx,pointery);
				pointery -= 100;
				drawImage(arrow.pixel_data,arrow.width,arrow.height,pointerx,pointery);
			}

			if(input == B && pointery == 320)
			{
				fillScreen(0x00000000);
				drawLevel1();
				drawImage(snake.pixel_data,snake.width,snake.height,4,4);

				gameStart = 1;
			}

			if(input == B && pointery == 420)
			{
				fillScreen(0x11111111);
				gameStart = 1;
			}
		}

		while(gameStart) {
			unsigned int lastInput = input;
			input = read_snes();

			if(input != lastInput)
			{
				if(input == UP)
				{
					drawImage(tile.pixel_data,tile.width,tile.height,gameStage.s.posx*32,gameStage.s.posy*32);
					gameStage.s.posy -= 1;
					drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
				}
				if(input == DOWN)
				{
					drawImage(tile.pixel_data,tile.width,tile.height,gameStage.s.posx*32,gameStage.s.posy*32);
					gameStage.s.posy += 1;
					drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
				}
				if(input == LEFT)
				{
					drawImage(tile.pixel_data,tile.width,tile.height,gameStage.s.posx*32,gameStage.s.posy*32);
					gameStage.s.posx -= 1;
					drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
				}
				if(input == RIGHT)
				{
					drawImage(tile.pixel_data,tile.width,tile.height,gameStage.s.posx*32,gameStage.s.posy*32);
					gameStage.s.posx += 1;
					drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
				}
			}
		}
}
