#include "framebuffer.h"
#include "level.h"
#include "snes.h"
#include <stdio.h>
#include <stdlib.h>
#include "myheader.h"

struct GameState gameStage;

int batMoveX[] = {8,9,10,11,12,13,14};

// LEVEL 1 DRAW METHOD
void drawLevel1(){
	//background
	for( int i = 0; i < 20;i++){
		for(int j = 0; j<20;j++){
			drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,i*32, j*32);
		}
	}

	//tiles (stationary enemy)
	for(int i = 0; i < 20;i++){
		for(int j = 0; j < 2; j++){
			drawImage(tile.pixel_data,tile.width,tile.height,i*32, j*32);
			gameStage.mapper[i][j] = 1;
		}
	}
	for(int i = 0; i < 2;i++){
		for(int j = 0; j < 20; j++){
			drawImage(tile.pixel_data,tile.width,tile.height,i*32, j*32);
			gameStage.mapper[i][j] = 1;
		}
	}
	for(int j = 0; j < 19;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,19*32, j*32);
		gameStage.mapper[19][j] = 1;
	}
	for(int j = 6; j < 18;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,10*32, j*32);
		gameStage.mapper[10][j] = 1;
	}

	for(int j = 8; j < 14;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,4*32, j*32);
		gameStage.mapper[4][j] = 1;
	}
	for(int j = 0; j < 4;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,15*32, j*32);
		gameStage.mapper[15][j] = 1;
	}
	for(int j = 15; j < 20;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,6*32, j*32);
		gameStage.mapper[6][j] = 1;
	}
	for(int j = 11; j < 18;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,15*32, j*32);
		gameStage.mapper[15][j] = 1;
	}
	for(int j = 7; j < 14;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,18*32, j*32);
		gameStage.mapper[18][j] = 1;
	}

	//holes
	drawImage(hole.pixel_data,hole.width,hole.height,8*32, 8*32);
	gameStage.mapper[8][8] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,15*32, 9*32);
	gameStage.mapper[15][9] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,2*32, 10*32);
	gameStage.mapper[2][10] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,6*32, 8*32);
	gameStage.mapper[6][8] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,8*32, 17*32);
	gameStage.mapper[8][17] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,12*32, 9*32);
	gameStage.mapper[12][9] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,6*32, 14*32);
	gameStage.mapper[6][14] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,16*32, 8*32);
	gameStage.mapper[16][8] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,15*32, 4*32);
	gameStage.mapper[15][4] = 2;

	//eggs
	if(gameStage.mapper[9][4] != 10)
	{
		drawImage(egglevelone.pixel_data,egglevelone.width,egglevelone.height,9*32, 4*32);
		gameStage.mapper[9][4] = 3;
	}
	if(gameStage.mapper[11][9] != 10)
	{
		drawImage(egglevelone.pixel_data,egglevelone.width,egglevelone.height,11*32, 9*32);
		gameStage.mapper[11][9] = 3;
	}
	if(gameStage.mapper[15][5] != 10)
	{
		drawImage(egglevelone.pixel_data,egglevelone.width,egglevelone.height,15*32, 5*32);
		gameStage.mapper[15][5] = 3;
	}
	if(gameStage.mapper[17][8] != 10)
	{
		drawImage(egglevelone.pixel_data,egglevelone.width,egglevelone.height,17*32, 8*32);
		gameStage.mapper[17][8] = 3;
	}
	if(gameStage.mapper[3][10] != 10)
	{
		drawImage(egglevelone.pixel_data,egglevelone.width,egglevelone.height,3*32, 10*32);
		gameStage.mapper[3][10] = 3;
	}

	//bat
	updateBatPos();

	//speed boost
	drawSpeedBoost();

	//extra lives
	drawExtraLives();

	//lives
	for(int i = 0; i < gameStage.lives; i++)
	{
		drawImage(heart.pixel_data,heart.width,heart.height,i*32,0);
	}	

	//score
	int num = gameStage.score;
	int digit;
	for(int i = 12; i > 9; i--)
	{
		digit = num % 10;
		switch (digit) {
			case 0:
				drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
				break;
			case 1:
				drawImage(one.pixel_data,one.width,one.height,i*32,0);
				break;
			case 2:
				drawImage(two.pixel_data,two.width,two.height,i*32,0);
				break;
			case 3:
				drawImage(three.pixel_data,three.width,three.height,i*32,0);
				break;
			case 4:
				drawImage(four.pixel_data,four.width,four.height,i*32,0);
				break;
			case 5:
				drawImage(five.pixel_data,five.width,five.height,i*32,0);
				break;
			case 6:
				drawImage(six.pixel_data,six.width,six.height,i*32,0);
				break;
			case 7:
				drawImage(seven.pixel_data,seven.width,seven.height,i*32,0);
				break;
			case 8:
				drawImage(eight.pixel_data,eight.width,eight.height,i*32,0);
				break;
			case 9:
				drawImage(nine.pixel_data,nine.width,nine.height,i*32,0);
				break;
		}
		num = num / 10;
	}

	//time
	num = gameStage.time;
	for(int i = 16; i > 14; i--)
	{
		digit = num % 10;
		switch (digit) {
			case 0:
				drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
				break;
			case 1:
				drawImage(one.pixel_data,one.width,one.height,i*32,0);
				break;
			case 2:
				drawImage(two.pixel_data,two.width,two.height,i*32,0);
				break;
			case 3:
				drawImage(three.pixel_data,three.width,three.height,i*32,0);
				break;
			case 4:
				drawImage(four.pixel_data,four.width,four.height,i*32,0);
				break;
			case 5:
				drawImage(five.pixel_data,five.width,five.height,i*32,0);
				break;
			case 6:
				drawImage(six.pixel_data,six.width,six.height,i*32,0);
				break;
			case 7:
				drawImage(seven.pixel_data,seven.width,seven.height,i*32,0);
				break;
			case 8:
				drawImage(eight.pixel_data,eight.width,eight.height,i*32,0);
				break;
			case 9:
				drawImage(nine.pixel_data,nine.width,nine.height,i*32,0);
				break;
		}
		num = num / 10;
	}

	//finish line
	drawImage(finish.pixel_data,finish.width,finish.height,19*32,19*32);
	gameStage.mapper[19][19] = 3;
}
// LEVEL 2 DRAW METHOD
void drawLevel2(){

	//background
	for( int i = 0; i < 20;i++){
		for(int j = 0; j<20;j++){
			drawImage(grass.pixel_data,grass.width,grass.height,i*32, j*32);
		}
	}
    
    // water (stationary enemy)
	for(int i = 0; i < 3;i++){
		for(int j = 0; j < 40; j++){
			drawImage(water.pixel_data,water.width,water.height,i*32, j*32);
			gameStage.mapper[i][j] = 1;
		}
	}
	for(int j = 38; j < 40;j++){
		for(int i = 0; i < 22; i++){
			drawImage(water.pixel_data,water.width,water.height,i*32, j*32);
			gameStage.mapper[i][j] = 1;
		}
	}
	for(int j = 0; j < 21;j++){
		drawImage(water.pixel_data,water.width,water.height,19*32, j*32);
		gameStage.mapper[3][j] = 1;
	}
	for(int i = 1; i < 39;i++){
		drawImage(water.pixel_data,water.width,water.height,10*32, j*32);
		gameStage.mapper[i][2] = 1;
	}

	for(int j = 8; j < 14;j++){
		drawImage(water.pixel_data,water.width,water.height,4*32, j*32);
		gameStage.mapper[4][j] = 1;
	}
	for(int j = 0; j < 4;j++){
		drawImage(water.pixel_data,water.width,water.height,15*32, j*32);
		gameStage.mapper[15][j] = 1;
	}
	for(int j = 25; j < 38 ;j++){
		drawImage(water.pixel_data,water.width,water.height,6*32, j*32);
		gameStage.mapper[19][j] = 1;
	}

	}
    //holes
	drawImage(hole.pixel_data,hole.width,hole.height,9*32, 9*32);
	gameStage.mapper[9][9] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,12*32, 7*32);
	gameStage.mapper[12][7] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,11*32, 9*32);
	gameStage.mapper[11][9] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,4*32, 7*32);
	gameStage.mapper[4][7] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,6*32, 3*32);
	gameStage.mapper[6][3] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,12*32, 9*32);
	gameStage.mapper[12][9] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,6*32, 15*32);
	gameStage.mapper[6][15] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,16*32, 8*32);
	gameStage.mapper[16][8] = 2;
	drawImage(hole.pixel_data,hole.width,hole.height,18*32, 9*32);
	gameStage.mapper[18][9] = 2;

    //bat
	updateBatPos();

	//speed boost
	drawSpeedBoost();

	//extra lives
	drawExtraLives();

	//lives
	for(int i = 0; i < gameStage.lives; i++)
	{
		drawImage(heart.pixel_data,heart.width,heart.height,i*32,0);
	}	

    //score
	int num = gameStage.score;
	int digit;
	for(int i = 12; i > 9; i--)
	{
		digit = num % 10;
		switch (digit) {
			case 0:
				drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
				break;
			case 1:
				drawImage(one.pixel_data,one.width,one.height,i*32,0);
				break;
			case 2:
				drawImage(two.pixel_data,two.width,two.height,i*32,0);
				break;
			case 3:
				drawImage(three.pixel_data,three.width,three.height,i*32,0);
				break;
			case 4:
				drawImage(four.pixel_data,four.width,four.height,i*32,0);
				break;
			case 5:
				drawImage(five.pixel_data,five.width,five.height,i*32,0);
				break;
			case 6:
				drawImage(six.pixel_data,six.width,six.height,i*32,0);
				break;
			case 7:
				drawImage(seven.pixel_data,seven.width,seven.height,i*32,0);
				break;
			case 8:
				drawImage(eight.pixel_data,eight.width,eight.height,i*32,0);
				break;
			case 9:
				drawImage(nine.pixel_data,nine.width,nine.height,i*32,0);
				break;
		}
		num = num / 10;
	
    //time
	num = gameStage.time;
	for(int i = 16; i > 14; i--)
	{
		digit = num % 10;
		switch (digit) {
			case 0:
				drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
				break;
			case 1:
				drawImage(one.pixel_data,one.width,one.height,i*32,0);
				break;
			case 2:
				drawImage(two.pixel_data,two.width,two.height,i*32,0);
				break;
			case 3:
				drawImage(three.pixel_data,three.width,three.height,i*32,0);
				break;
			case 4:
				drawImage(four.pixel_data,four.width,four.height,i*32,0);
				break;
			case 5:
				drawImage(five.pixel_data,five.width,five.height,i*32,0);
				break;
			case 6:
				drawImage(six.pixel_data,six.width,six.height,i*32,0);
				break;
			case 7:
				drawImage(seven.pixel_data,seven.width,seven.height,i*32,0);
				break;
			case 8:
				drawImage(eight.pixel_data,eight.width,eight.height,i*32,0);
				break;
			case 9:
				drawImage(nine.pixel_data,nine.width,nine.height,i*32,0);
				break;
		}
		num = num / 10;
	}

	//finish line
	drawImage(finish.pixel_data,finish.width,finish.height,19*32,19*32);
	gameStage.mapper[19][19] = 3;

}
void initGameState()
{
	gameStage.time = 60;
	gameStage.eggsEaten = 0;
	gameStage.lives = 4;
	gameStage.s.speed = 200000;
	gameStage.batPosX = 7;
	gameStage.batPosY = 18;
	if (gameStage.currentLevel == 1)
	{
		gameStage.s.posx = 4;
		gameStage.s.posy = 4;
	}
	gameStage.score = (5*gameStage.eggsEaten) + 2*(gameStage.lives + gameStage.time);
	for( int i = 0; i < 20;i++){
		for(int j = 0; j<20;j++){
			gameStage.mapper[i][j] = 0;
		}
	}
}

void updateScore()
{
	int num = gameStage.score;
	for(int i = 12; i > 9; i--)
	{
		int digit = num % 10;
		if(digit == 0)
		{
			drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
		}
		switch (digit) {
			case 0:
				drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
				break;
			case 1:
				drawImage(one.pixel_data,one.width,one.height,i*32,0);
				break;
			case 2:
				drawImage(two.pixel_data,two.width,two.height,i*32,0);
				break;
			case 3:
				drawImage(three.pixel_data,three.width,three.height,i*32,0);
				break;
			case 4:
				drawImage(four.pixel_data,four.width,four.height,i*32,0);
				break;
			case 5:
				drawImage(five.pixel_data,five.width,five.height,i*32,0);
				break;
			case 6:
				drawImage(six.pixel_data,six.width,six.height,i*32,0);
				break;
			case 7:
				drawImage(seven.pixel_data,seven.width,seven.height,i*32,0);
				break;
			case 8:
				drawImage(eight.pixel_data,eight.width,eight.height,i*32,0);
				break;
			case 9:
				drawImage(nine.pixel_data,nine.width,nine.height,i*32,0);
				break;
		}
		num = num / 10;
	}
}

void updateTime()
{
	int num = gameStage.time;
	for(int i = 16; i > 14; i--)
	{
		int digit = num % 10;
		if(digit == 0)
		{
			drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
		}
		switch (digit) {
			case 0:
				drawImage(zero.pixel_data,zero.width,zero.height,i*32,0);
				break;
			case 1:
				drawImage(one.pixel_data,one.width,one.height,i*32,0);
				break;
			case 2:
				drawImage(two.pixel_data,two.width,two.height,i*32,0);
				break;
			case 3:
				drawImage(three.pixel_data,three.width,three.height,i*32,0);
				break;
			case 4:
				drawImage(four.pixel_data,four.width,four.height,i*32,0);
				break;
			case 5:
				drawImage(five.pixel_data,five.width,five.height,i*32,0);
				break;
			case 6:
				drawImage(six.pixel_data,six.width,six.height,i*32,0);
				break;
			case 7:
				drawImage(seven.pixel_data,seven.width,seven.height,i*32,0);
				break;
			case 8:
				drawImage(eight.pixel_data,eight.width,eight.height,i*32,0);
				break;
			case 9:
				drawImage(nine.pixel_data,nine.width,nine.height,i*32,0);
				break;
		}
		num = num / 10;
	}
}

void updateLives()
{
	for(int i = 0; i < gameStage.lives; i++)
	{
		drawImage(heart.pixel_data,heart.width,heart.height,i*32,0);
	}
}

void drawSpeedBoost()
{
	if(gameStage.mapper[14][9] != 10 && gameStage.time < 30)
	{
		drawImage(speed.pixel_data,speed.width,speed.height,14*32, 9*32);
		gameStage.mapper[14][9] = 4;
	}
}

void drawExtraLives()
{
	if(gameStage.mapper[17][5] != 10 && gameStage.time < 20)
	{
		drawImage(extralife.pixel_data,extralife.width,extralife.height,17*32, 5*32);
		gameStage.mapper[17][5] = 5;
	}

}

void updateBatPos()
{
	if(gameStage.batPosX < 18)
	{
		drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.batPosX*32,gameStage.batPosY*32);
		gameStage.mapper[gameStage.batPosX][gameStage.batPosY] = 2;
		gameStage.batPosX += 1;
		drawImage(bat.pixel_data,bat.width,bat.height,gameStage.batPosX*32,gameStage.batPosY*32);
		gameStage.mapper[gameStage.batPosX-1][gameStage.batPosY] = 0;
	}
	else if(gameStage.batPosX == 18)
	{
		drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,gameStage.batPosX*32,gameStage.batPosY*32);
		gameStage.mapper[gameStage.batPosX][gameStage.batPosY] = 2;
		gameStage.batPosX = 7;
		drawImage(bat.pixel_data,bat.width,bat.height,gameStage.batPosX*32,gameStage.batPosY*32);
		gameStage.mapper[gameStage.batPosX][gameStage.batPosY] = 2;
	}

	
}
