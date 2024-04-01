
#include "gpio.h"
#include "uart.h"
#include "snes.h"
#include "framebuffer.h"
#include "level.h"
//#include "myheader.h"
//#include "images/lev1.h"
#include "images/snake.h"
#include "images/fence.h"
#include "images/starts.h"
#include "images/arrow.h"
#include "images/antipointer.h"
#include "images/paused.h"
#include "images/startoverbtn.h"
#include "images/quit.h"
#include "images/youlose.h"
#define GPIO_BASE 0xFE200000
#define CLK_REG 0xFE003004

int gameStart = 0;
int gamePaused = 0;
int gameLost = 0;

void printf(char *str) {
	uart_puts(str);
}

void handleDeath()
	{
		gameStage.lives -= 1;
		if(gameStage.lives > 0) 
		{
			gameStage.s.posx = gameStage.startx;
			gameStage.s.posy = gameStage.starty;
			if(gameStage.currentLevel == 1)
			{
				fillScreen(0x00000000);
				drawLevel1();
					
			}
			else
			{
				//drawLevel2();
			}
			drawImage(snake.pixel_data,snake.width,snake.height,gameStage.startx*32,gameStage.starty*32);
		}
		else
		{
			//display lost screen
			gameStart = 0;
			gameLost = 1;
							
		}
	}

void handleBatCollision()
{
	if((gameStage.batPosX + 1) == gameStage.s.posx && gameStage.batPosY == gameStage.s.posx)
	{
			printf("yeaaa");
			handleDeath();
	}
}

int main(){
	init_snes_lines();
    init_framebuffer(); // You can use framebuffer, width, height and pitch variables available in framebuffer.h
	unsigned *startTime = (unsigned *) CLK_REG;

	unsigned int lastInput; 

    gameStage.lives = 4;
    gameStage.currentLevel = 1;
	gameStage.s.isShielded = 0;
	gameStage.s.posx = 4;
	gameStage.s.posy = 4;
	gameStage.s.speed = 200000;
	gameStage.startx = 4;
	gameStage.starty = 4;
	gameStage.score = 0;

    fillScreen(0x00000000);

    int pointerx = 200;
    int pointery = 320;

	int arrowx = 6*32;
	int arrowy = 10*32;
    drawImage(starts.pixel_data,starts.width,starts.height,256,152);
    drawImage(arrow.pixel_data, arrow.width,arrow.height,pointerx,pointery);
	unsigned int input = read_snes();

	while(1) 
	{
		//MAIN MENU
		
		while(!gameStart && !gamePaused) 
		{
			input = read_snes();
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

			if(input == A && pointery == 320)
			{
				gameStage.currentLevel = 1;
				initGameState();
				fillScreen(0x00000000);
				drawLevel1();
				drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);

				gameStart = 1;
			}

			if(input == A && pointery == 420)
			{
				fillScreen(0x11111111);
				gameStart = 0;
			}
		}

		unsigned nextSecond = *startTime + 1000000;
		unsigned nextQuarterSec = *startTime + 200000;
		//GAME INTERFACE
		while(gameStart && !gamePaused) {

			if(*startTime > nextSecond)
			{
				gameStage.time -= 1;
				gameStage.score = (5*gameStage.eggsEaten) + 2*(gameStage.lives + gameStage.time);
				updateScore();
				updateTime();
				nextSecond += 1000000;
			}

			if(*startTime > nextQuarterSec)
			{
				updateBatPos();
				nextQuarterSec += 200000;
			}

			handleBatCollision();
			drawExtraLives();
			drawSpeedBoost();
			lastInput = input;
			input = read_snes();
			
				if(input == UP)
				{
					if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy-1)] == 1) 
					{
						
						continue;

					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy-1)] == 2)
					{
						handleDeath();
					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy-1)] == 3)
					{
						gameStage.eggsEaten += 1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						wait(gameStage.s.speed);
					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy-1)] == 4)
					{
						gameStage.s.speed /= 2;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						wait(gameStage.s.speed);

					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy-1)] == 5)
					{
						gameStage.lives += 1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						updateLives();
						wait(gameStage.s.speed);
					}
					else{
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						wait(gameStage.s.speed);
					}
				}
				if(input == DOWN)
				{
					if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy+1)] == 1) 
					{
						printf("it work");
						continue;

					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy+1)] == 2)
					{
						handleDeath();
					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy+1)] == 3)
					{
						gameStage.eggsEaten +=1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						wait(gameStage.s.speed);
					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy+1)] == 4)
					{
						gameStage.s.speed /= 2;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						wait(gameStage.s.speed);

					}
					else if(gameStage.mapper[gameStage.s.posx][(gameStage.s.posy+1)] == 5)
					{
						gameStage.lives += 1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						updateLives();
						wait(gameStage.s.speed);
					}
					else{
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posy += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						wait(gameStage.s.speed);
					}
				}
				if(input == LEFT)
				{
					if(gameStage.mapper[gameStage.s.posx-1][(gameStage.s.posy)] == 1) 
					{
						printf("it work");
						continue;

					}
					else if(gameStage.mapper[gameStage.s.posx-1][(gameStage.s.posy)] == 2)
					{
						handleDeath();
					}
					else if(gameStage.mapper[gameStage.s.posx-1][(gameStage.s.posy)] == 3)
					{
						gameStage.eggsEaten +=1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						wait(gameStage.s.speed);
					}
					else if(gameStage.mapper[gameStage.s.posx-1][(gameStage.s.posy)] == 4)
					{
						gameStage.s.speed /= 2;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						wait(gameStage.s.speed);

					}
					else if(gameStage.mapper[gameStage.s.posx-1][(gameStage.s.posy)] == 5)
					{
						gameStage.lives += 1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						updateLives();
						wait(gameStage.s.speed);
					}
					else{
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx -= 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						wait(gameStage.s.speed);
					}
				}
				if(input == RIGHT)
				{
					if(gameStage.mapper[gameStage.s.posx+1][(gameStage.s.posy)] == 1) 
					{
						printf("it work");
						continue;

					}
					else if(gameStage.mapper[gameStage.s.posx+1][(gameStage.s.posy)] == 2)
					{
						handleDeath();
					}
					else if(gameStage.mapper[gameStage.s.posx+1][(gameStage.s.posy)] == 3)
					{
						gameStage.eggsEaten +=1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10; 
						wait(gameStage.s.speed);
					}
					else if(gameStage.mapper[gameStage.s.posx+1][(gameStage.s.posy)] == 4)
					{
						gameStage.s.speed /= 2;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						wait(gameStage.s.speed);

					}
					else if(gameStage.mapper[gameStage.s.posx+1][(gameStage.s.posy)] == 5)
					{
						gameStage.lives += 1;
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.mapper[gameStage.s.posx][gameStage.s.posy] = 10;
						updateLives();
						wait(gameStage.s.speed);
					}
					else{
						drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.s.posx*32,gameStage.s.posy*32);
						gameStage.s.posx += 1;
						drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
						wait(gameStage.s.speed);
					}
				}

				if(input == START && gamePaused == 0)
				{
					gamePaused = 1;
					gameStart = 0;
					drawRect(1*32,1*32,19*32,19*32,0x00000000,1);
					drawImage(paused.pixel_data,paused.width,paused.height,7*32,2*32);
					drawImage(startoverbtn.pixel_data,startoverbtn.width,startoverbtn.height,7*32,10*32);
					drawImage(quit.pixel_data,quit.width,quit.height,7*32,15*32);
					drawImage(arrow.pixel_data,arrow.width,arrow.height,arrowx,arrowy);
				}
				if(gameStage.time <= 0)
				{
					gameStart = 0;
					gameLost = 1;
				}
		}


		//PAUSE MENU
		while (gamePaused && !gameStart)
		{
			printf("pausemenu");
			lastInput = input;
			input = read_snes();

			if(input == DOWN)
			{
				drawImage(antipointer.pixel_data,antipointer.width,antipointer.height,arrowx,arrowy);
				arrowy = 15*32;
				drawImage(arrow.pixel_data,arrow.width,arrow.height,arrowx,arrowy);
			}

			if(input == UP)
			{
				drawImage(antipointer.pixel_data,antipointer.width,antipointer.height,arrowx,arrowy);
				arrowy = 10*32;
				drawImage(arrow.pixel_data,arrow.width,arrow.height,arrowx,arrowy);
			}

			if(input == START && lastInput != START)
			{	
				gamePaused = 0;
				gameStart = 1;
				drawLevel1();
				drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
			}

			if(input == A && arrowy == 10*32)
			{
				gamePaused = 0;
				gameStart = 1;
				initGameState();
				drawLevel1();
				drawImage(snake.pixel_data,snake.width,snake.height,gameStage.s.posx*32,gameStage.s.posy*32);
			}

			else if(input == A && arrowy == 15*32)
			{
				gamePaused = 0;
				fillScreen(0x00000000);
				drawImage(starts.pixel_data,starts.width,starts.height,1,1);
    			drawImage(arrow.pixel_data, arrow.width,arrow.height,pointerx,pointery);
			}

		}
		while(gameLost)
		{
			fillScreen(0x00000000);
			drawImage(youlose.pixel_data,youlose.width,youlose.height,1,1);
			wait(4*1000000);
			fillScreen(0x00000000);
			drawImage(starts.pixel_data,starts.width,starts.height,1,1);
    		drawImage(arrow.pixel_data, arrow.width,arrow.height,pointerx,pointery);
			gameLost = 0;
		}
	}
}
