#include "framebuffer.h"
#include "level.h"
#include "snes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myheader.h"

struct GameState gameStage;


// LEVEL 1 DRAW METHOD
void drawLevel1(){

	gameStage.currentLevel = 0;
	for( int i = 0; i < 20;i++){
		for(int j = 0; j<20;j++){
			drawImage(fencepic.pixel_data,fencepic.width,fencepic.height,i*32, j*32);
			gameStage.mapper[i][j] = 0;
		}
	}


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

	for(int j = 6; j < 20;j++){
		drawImage(tile.pixel_data,tile.width,tile.height,10*32, j*32);
		gameStage.mapper[10][j] = 1;
	}

	/*int j = 21;
	for(int i = 0; i < 20;i++){
		drawImage(tile.pixel_data,tile.width,tile.height,j*32, i*32);
		gameStage.mapper[j][i] = 1;
		drawImage(tile.pixel_data,tile.width,tile.height,(j-1)*32, i*32);
		gameStage.mapper[j-1][i] = 1;
	}
	for(j = 8; j< 19;j++){
		drawImage(fire.pixel_data,fire.width,fire.height,j*32, 19*32);
		//gameStage.mapper[19][j] = fire;
	}

	for(int i = 0; i < (gameStage.lives); i++){
		drawImage(tile.pixel_data,tile.width,tile.height,0, i*32);
	}
	
	// DRAW PLATFORMS

	gameStage.starti = 3*32;
	gameStage.startj = 3*32;
	for(int j = 3; j < 3; j++){
		drawImage(tile.pixel_data,tile.width,tile.height,32, (4)*32);
		gameStage.mapper[4][j] = 1;
	}

	for(int j = 3; j < 5; j++){
		drawImage(tile.pixel_data,tile.width,tile.height,32, (7)*32);
		gameStage.mapper[7][j] = 1;

	}

	for(int j = 12; j< 9; j++){
		drawImage(tile.pixel_data,tile.width,tile.height,32, (10)*32);
		gameStage.mapper[10][j] = 1;

	}

	for(int j = 3; j< 12; j++){
		drawImage(tile.pixel_data,tile.width,tile.height,32, (13)*32);
		gameStage.mapper[13][j] = 1;
	}

	for(int j = 13; j< 15; j++){
		drawImage(tile.pixel_data,tile.width,tile.height,32, (16)*32);
		gameStage.mapper[16][j] = 1;
	}

	for(int j = 3; j< 18; j++){
		drawImage(tile.pixel_data,tile.width,tile.height,32, (19)*32);
		gameStage.mapper[19][j] = 1;
	}


	gameStage.endi = 18*32;
	gameStage.endj = 24*32;
	drawImage(lev1.pixel_data,lev1.width,lev1.height,576, 1);
	//drawImage(gameStage.endj, gameStage.endi + 32, &tilemap.images[pointer]);

	*/
}
/*
// LEVEL 2 DRAW METHOD
void drawLevel2(){

	gameStage.currentLevel = 1;
	for( int k = 0; k<22;k++){
		for(int j = 0; j<20;j++){
			drawImage(j*32, k*32, &tilemap.images[grass]);
			gameStage.mapper[k][j] = 0;
		}
	}


	for(int i = 0; i < 3;i++){
	for(int j = 0; j<20; j++){
		drawImage(j*32, i*32, &tilemap.images[water]);
		gameStage.mapper[i][j] = 1;
	}
	}
	for(int j = 38; j < 20;j++){
		for(int i = 0; i<22; i++){
			drawImage(j*32, i*32, &tilemap.images[water]);
			gameStage.mapper[i][j] = 1;
		}
	}
	for(int i = 0; i < 3;i++){
		for(int j = 0; j<21; j++){
			drawImage(i*32, j*32, &tilemap.images[water]);
			gameStage.mapper[j][i] = 1;
		}
	}

	for(int i = 1; i < 39;i++){
		drawImage(i*32, 64, &tilemap.images[water]);
		gameStage.mapper[2][i] = 1;
	}

	for(int j = 25; j< 38;j++){
		drawImage(j*32, (19*32), &tilemap.images[water]);
		gameStage.mapper[19][j] = 1;
	}

	for(int j = 0; j< (gameStage.lives);j++){
		drawImage(0, j*32, &tilemap.images[heart]);
	}

	int j = 21;
	for(int i = 0; i < 20;i++){
		drawImage(i*32, j*32, &tilemap.images[water]);
		gameStage.mapper[j][i] = 1;
		drawImage(i*32, (j-1)*32, &tilemap.images[water]);
		gameStage.mapper[j-1][i] = 1;
	}

	// DRAW PLATFORMS

	gameStage.starti = 3*32;
	gameStage.startj = 24*32;
	for(int j = 3; j < 25; j++){
		drawImage(j*32, (4)*32, &tilemap.images[water]);
		gameStage.mapper[4][j] = 1;
	}

	for(int j = 20; j < 38; j++){
		drawImage(j*32, (7)*32, &tilemap.images[water]);
		gameStage.mapper[7][j] = 1;

	}

	for(int j = 12; j< 38; j++){
		drawImage(j*32, (10)*32, &tilemap.images[water]);
		gameStage.mapper[10][j] = 1;

	}

	for(int j = 3; j< 18; j++){
		drawImage(j*32, (13)*32, &tilemap.images[water]);
		gameStage.mapper[13][j] = 1;
	}

	for(int j = 3; j< 27; j++){
		drawImage(j*32, (16)*32, &tilemap.images[water]);
		gameStage.mapper[16][j] = 1;
	}

	for(int j = 3; j< 38; j++){
		drawImage(j*32, (19)*32, &tilemap.images[water]);
		gameStage.mapper[19][j] = 1;
	}

	gameStage.endi = 18*32;
	gameStage.endj = 36*32;
	drawImage(576, 1, &tilemap.images[level2]);
	drawImage(gameStage.endj, gameStage.endi + 32, &tilemap.images[pointer]);

}

// LEVEL 3 DRAW METHOD
void drawLevel3(){

	gameStage.currentLevel = 2;
	for( int k = 0; k<22;k++){
		for(int j = 0; j<20;j++){
			drawImage(j*32, k*32, &tilemap.images[water]);
			gameStage.mapper[k][j] = 0;
		}
	}

	for(int i = 0; i < 3;i++){
	for(int j = 0; j<22; j++){
		drawImage(i*32, j*32, &tilemap.images[tile]);
		gameStage.mapper[j][i] = 1;
	}
	}
	for(int i = 38; i < 20;i++){
		for(int j = 0; j<22; j++){
			drawImage(i*32, j*32, &tilemap.images[tile]);
			gameStage.mapper[j][i] = 1;
		}
	}
	for(int i = 0; i < 3;i++){
		for(int j = 0; j<21; j++){
			drawImage(i*32, j*32, &tilemap.images[tile]);
			gameStage.mapper[j][i] = 1;
		}
	}

	for(int i = 1; i < 38;i++){
		for(int j = 0; j<3;j++){
		drawImage(i*32, j*32, &tilemap.images[tile]);
		gameStage.mapper[j][i] = 1;
		}
	}

	for(int i = 0; i < 39;i++){
		drawImage(i*32, 21*32, &tilemap.images[tile]);
		gameStage.mapper[21][i] = 1;
		drawImage(i*32, 20*32, &tilemap.images[tile]);
		gameStage.mapper[20][i] = 1;
	}


	for(int j = 0; j< (gameStage.lives);j++){
		drawImage(0, j*32, &tilemap.images[heart]);
	}

	for(int j = 3; j< 23; j++){
		drawImage(j*32, 19*32, &tilemap.images[fire]);
		gameStage.mapper[19][j] = fire;
	}
	// DRAW PLATFORMS

	gameStage.starti = 3*32;
	gameStage.startj = 25*32;
	for(int j = 25; j < 38; j++){
		drawImage(j*32, (4)*32, &tilemap.images[tile]);
		gameStage.mapper[4][j] = 1;
	}


	for(int j = 3; j < 26; j++){
		drawImage(j*32, (7)*32, &tilemap.images[tile]);
		gameStage.mapper[7][j] = 1;

	}

	for(int j = 12; j< 38; j++){
		drawImage(j*32, (10)*32, &tilemap.images[tile]);
		gameStage.mapper[10][j] = 1;

	}

	for(int j = 3; j< 20; j++){
		drawImage(j*32, (13)*32, &tilemap.images[tile]);
		gameStage.mapper[13][j] = 1;
	}

	for(int j = 3; j< 27; j++){
		drawImage(j*32, (16)*32, &tilemap.images[tile]);
		gameStage.mapper[16][j] = 1;
	}

	for(int j = 23; j< 38; j++){
		drawImage(j*32, (19)*32, &tilemap.images[tile]);
		gameStage.mapper[19][j] = 1;
	}

	gameStage.endi = 18*32;
	gameStage.endj = 37*32;
	drawImage(576, 1, &tilemap.images[level3]);
	drawImage(gameStage.endj, gameStage.endi + 32, &tilemap.images[pointer]);

}

// LEVEL 4 DRAW METHOD
void drawLevel4(){

	gameStage.currentLevel = 3;
	for( int k = 0; k<22;k++){
		for(int j = 0; j<20;j++){
			drawImage(j*32, k*32, &tilemap.images[tile]);
			gameStage.mapper[k][j] = 0;
		}
	}

	for(int i = 0; i < 3;i++){
	for(int j = 0; j<22; j++){
		drawImage(i*32, j*32, &tilemap.images[water]);
		gameStage.mapper[j][i] = 1;
	}
	}
	for(int i = 38; i < 20;i++){
		for(int j = 0; j<22; j++){
			drawImage(i*32, j*32, &tilemap.images[water]);
			gameStage.mapper[j][i] = 1;
		}
	}
	for(int i = 0; i < 3;i++){
		for(int j = 0; j<21; j++){
			drawImage(i*32, j*32, &tilemap.images[water]);
			gameStage.mapper[j][i] = 1;
		}
	}

	for(int i = 1; i < 39;i++){
		for(int j = 0; j < 3; j++){
		drawImage(i*32, j*32, &tilemap.images[water]);
		gameStage.mapper[j][i] = 1;
		}
	}

	for(int i = 1; i < 39;i++){
		for(int j = 20; j < 22; j++){
		drawImage(i*32, j*32, &tilemap.images[water]);
		gameStage.mapper[j][i] = 1;
		}
	}


	// for(int i = 0; i < 39;i++){
	// 	drawImage(i*32, 21*32, &tilemap.images[fire]);
	// 	gameStage.mapper[21][i] = 1;
	// }

	for(int j = 0; j< (gameStage.lives);j++){
		drawImage(0, j*32, &tilemap.images[heart]);
	}

	// DRAW PLATFORMS

	gameStage.starti = 3*32;
	gameStage.startj = 25*32;

	for(int j = 25; j < 38; j++){
		drawImage(j*32, (4)*32, &tilemap.images[grass]);
		gameStage.mapper[4][j] = 1;
	}

	for(int j = 3; j < 26; j++){
		drawImage(j*32, (7)*32, &tilemap.images[grass]);
		gameStage.mapper[7][j] = 1;

	}

	for(int j = 12; j< 38; j++){
		drawImage(j*32, (10)*32, &tilemap.images[grass]);
		gameStage.mapper[10][j] = 1;

	}

	for(int j = 7; j< 38; j++){
		drawImage(j*32, (13)*32, &tilemap.images[grass]);
		gameStage.mapper[13][j] = 1;
	}

	for(int j = 3; j< 27; j++){
		drawImage(j*32, (16)*32, &tilemap.images[grass]);
		gameStage.mapper[16][j] = 1;
	}

	for(int j = 23; j< 38; j++){
		drawImage(j*32, (19)*32, &tilemap.images[grass]);
		gameStage.mapper[19][j] = 1;

	}

	for(int j = 3; j< 23; j++){
		drawImage(j*32, 19*32, &tilemap.images[fire]);
		gameStage.mapper[19][j] = fire;
	}
	gameStage.endi = 18*32;
	gameStage.endj = 37*32;
	drawImage(576, 1, &tilemap.images[level4]);
	drawImage(gameStage.endj, gameStage.endi + 32, &tilemap.images[pointer]);


}

// LEVEL 5 DRAW METHOD
void drawLevel5(){

	gameStage.currentLevel = 4;
	for( int k = 0; k<22;k++){
		for(int j = 0; j<20;j++){
			drawImage(j*32, k*32, &tilemap.images[water]);
			gameStage.mapper[k][j] = 0;
		}
	}

	for(int i = 0; i < 3;i++){
	for(int j = 0; j<22; j++){
		drawImage(i*32, j*32, &tilemap.images[tile]);
		gameStage.mapper[j][i] = 1;
	}
	}
	for(int i = 38; i < 20;i++){
		for(int j = 0; j<22; j++){
			drawImage(i*32, j*32, &tilemap.images[tile]);
			gameStage.mapper[j][i] = 1;
		}
	}
	for(int i = 0; i < 3;i++){
		for(int j = 0; j<21; j++){
			drawImage(i*32, j*32, &tilemap.images[tile]);
			gameStage.mapper[j][i] = 1;
		}
	}

	for(int i = 1; i < 39;i++){
		for(int j = 0; j <3; j++){
		drawImage(i*32, j*32, &tilemap.images[tile]);
		gameStage.mapper[j][i] = 1;
		}
	}

	for(int i = 1; i < 39;i++){
		for(int j = 20; j <22; j++){
		drawImage(i*32, j*32, &tilemap.images[tile]);
		gameStage.mapper[j][i] = 1;
		}
	}

	for(int j = 0; j< (gameStage.lives);j++){
		drawImage(0, j*32, &tilemap.images[heart]);
	}

	// DRAW PLATFORMS

	// initialize start coordinates of current level
	gameStage.starti = 3*32;
	gameStage.startj = 25*32;
	for(int j = 5; j < 38; j++){
		drawImage(j*32, (4)*32, &tilemap.images[grass]);
		gameStage.mapper[4][j] = 1;
	}

	for(int j = 3; j < 26; j++){
		drawImage(j*32, (7)*32, &tilemap.images[grass]);
		gameStage.mapper[7][j] = 1;

	}

	for(int j = 12; j< 38; j++){
		drawImage(j*32, (10)*32, &tilemap.images[grass]);
		gameStage.mapper[10][j] = 1;

	}

	for(int j = 3; j< 14; j++){
		drawImage(j*32, (13)*32, &tilemap.images[grass]);
		gameStage.mapper[13][j] = 1;
	}

	for(int j = 3; j< 27; j++){
		drawImage(j*32, (16)*32, &tilemap.images[grass]);
		gameStage.mapper[16][j] = 1;
	}

	for(int j = 3; j< 38; j++){
		drawImage(j*32, (19)*32, &tilemap.images[grass]);
		gameStage.mapper[19][j] = 1;
	}

	// initialize end coordinates of current level
	gameStage.endi = 18*32;
	gameStage.endj = 10*32;
	drawImage(gameStage.endj - 32, gameStage.endi, &tilemap.images[kong]);
	gameStage.mapper[(gameStage.endi/32)][(gameStage.endj/32) -1] = 1;
	drawImage(gameStage.endj - 32, gameStage.endi - 32, &tilemap.images[kong]);
	gameStage.mapper[(gameStage.endi/32) - 1][(gameStage.endj/32) - 1] = 1;
	drawImage(gameStage.endj - 64, gameStage.endi - 32, &tilemap.images[kong]);
	gameStage.mapper[(gameStage.endi/32) - 2][(gameStage.endj/32) - 1] = 1;
	drawImage(576, 1, &tilemap.images[level5]);
	drawImage(gameStage.endj, gameStage.endi + 32, &tilemap.images[pointer]);

}


Mehtod to interact with the pause menu when the START button input is read from GPIO.

Returns 0 to CONTINUE or 1 to QUIT.



int paused (){

	// Coordiantes to refer to for where the CONTINUE and QUIT images are printed.
	int x = 486;
	int y = 374;

	// var to read from snes
	unsigned int result;

	// var to indicate quit or continue. Initialise to 0 to indicate quit.
	int quitstat = 0;

	// pointer is blue indicating current selecting and pointer 2 is black indicationg alternate selection.
	drawImage(x, y, &tilemap.images[pointer]);
	drawImage(x, y+120, &tilemap.images[pointer2]);

	while(1){
		result = read_snes();
		// If A is read from GPIO then a value is returned depending on the state of quitstat
		if((result == A) & (quitstat  == 0)){
			return 0;
		}else if((result == A) & (quitstat == 1)){
			return 1;
		}

		if(result == DOWN){
			if(y == 374){
				drawImage(x, y, &tilemap.images[pointer2]);
				y += 120;
				drawImage(x, y, &tilemap.images[pointer]);
				drawImage(528, 324, &tilemap.images[continuescreen]);
				quitstat = 1;
				continue;
			}
		}

		if(result == UP){
			if(y == 494){
				drawImage(x, y, &tilemap.images[pointer2]);
				y -= 120;
				drawImage(x, y, &tilemap.images[pointer]);
				drawImage(528, 444, &tilemap.images[quit]);
				quitstat = 0;
				continue;
			}
		}

		if(result == START){
			return 0;
		}

	}	
}


Mehtod to interact with the main screen so that we can decide to start a new game or to exit the game.

Return 1 for QUIT or 0 to START new game

int MainScreen(){
	drawImage(33, 32, &tilemap.images[homescreen]);
	drawImage(528, 400, &tilemap.images[start]);
	drawImage(528, 520, &tilemap.images[quit]);
	drawImage(640, 1, &tilemap.images[instruct]);

	int x = 486;
	int y = 450;
	unsigned int result;
	int quitstat = 0;
	drawImage(x, y, &tilemap.images[pointer]);
	drawImage(x, y+120, &tilemap.images[pointer2]);

	while(1){
	result = read_snes();

	if((result == A) & (quitstat  == 0)){
		return 0;
	}else if((result == A) & (quitstat == 1)){
		return 1;
	}

	if(result == DOWN){
		if(y == 450){
			drawImage(x, y, &tilemap.images[pointer2]);
			y += 120;
			drawImage(x, y, &tilemap.images[pointer]);
			quitstat = 1;
			continue;
		}
	}

	if(result == UP){
		if(y == 570){
			drawImage(x, y, &tilemap.images[pointer2]);
			y -= 120;
			drawImage(x, y, &tilemap.images[pointer]);
			quitstat = 0;
			continue;
		}
	}

	}
}

/*
The following method resets the current gameStage to the level 1 gameStage.

void reset(){
	gameStage.currentLevel = 0;
	gameStage.lives = 4;

	gameStage.starti = 3*32;
	gameStage.startj = 3*32;

	gameStage.endi = 18*32;
	gameStage.endj = 24*32;

	gameStage.bananas = 0;
	gameStage.mapper[3][14] = food;
	gameStage.mapper[6][6] = food;
	gameStage.mapper[9][12] = food;
	gameStage.mapper[12][16] = food;
	gameStage.mapper[15][37] = food;
	gameStage.mapper[18][20] = food;
	gameStage.score = 0;

}

/**
The following method takes parameter input of level number and initializes locations on the gameStage for the level number that is passed in which is (level_number - 1)

i.e If level is level 5 then the parameter is 5-1 which is 4.


void initLevel(int level){


	if(level == 0){//L1
		//WATER
		gameStage.mapper[3][14] = food;
		gameStage.mapper[6][6] = food;
		gameStage.mapper[9][12] = food;
		gameStage.mapper[12][16] = food;
		gameStage.mapper[15][37] = food;
		gameStage.mapper[18][20] = food;
		
		// FIRE
		gameStage.mapper[6][10] = fire;
		gameStage.mapper[9][14] = fire;
		gameStage.mapper[12][12] = fire;
		gameStage.mapper[15][29] = fire;
		gameStage.mapper[18][15] = fire;
		gameStage.lives = 4;
		gameStage.score = 0;
	}
	if(level == 1){//L2
		//WATER
		gameStage.mapper[3][10] = food;
		gameStage.mapper[6][20] = food;
		gameStage.mapper[9][20] = food;
		gameStage.mapper[12][17] = food;
		gameStage.mapper[15][12] = food;
		gameStage.mapper[18][35] = food;
		
		// FIRE
		gameStage.mapper[6][23] = fire;
		gameStage.mapper[9][24] = fire;
		gameStage.mapper[12][12] = fire;
		gameStage.mapper[15][15] = fire;
		gameStage.mapper[18][30] = fire;
		copyObjects();
	}
	if( level == 2){//L3
		//WATER
		gameStage.mapper[3][30] = food;
		gameStage.mapper[6][17] = food;
		gameStage.mapper[9][17] = food;
		gameStage.mapper[9][15] = food;
		gameStage.mapper[12][11] = food;
		gameStage.mapper[15][11] = food;
		gameStage.mapper[18][36] = food;
		
		// FIRE
		gameStage.mapper[6][20] = fire;
		gameStage.mapper[9][24] = fire;
		gameStage.mapper[9][23] = fire;
		gameStage.mapper[9][22] = fire;
		gameStage.mapper[12][13] = fire;
		gameStage.mapper[15][13] = fire;
		gameStage.mapper[18][34] = fire;
		copyObjects();
	}
	if(level == 3){//L4
		//WATER
		gameStage.mapper[3][30] = food;
		gameStage.mapper[6][17] = food;
		gameStage.mapper[9][17] = food;
		gameStage.mapper[9][15] = food;
		gameStage.mapper[12][11] = food;
		gameStage.mapper[15][11] = food;
		gameStage.mapper[18][36] = food;
		
		// FIRE
		gameStage.mapper[6][20] = fire;
		gameStage.mapper[9][24] = fire;
		gameStage.mapper[9][23] = fire;
		gameStage.mapper[9][22] = fire;
		gameStage.mapper[12][13] = fire;
		gameStage.mapper[15][13] = fire;
		gameStage.mapper[18][34] = fire;
		copyObjects();
	}
	if(level == 4){//L5
		//WATER
		gameStage.mapper[3][30] = food;
		gameStage.mapper[6][17] = food;
		gameStage.mapper[9][17] = food;
		gameStage.mapper[9][15] = food;
		gameStage.mapper[12][11] = food;
		gameStage.mapper[15][11] = food;
		gameStage.mapper[18][36] = food;
		
		// FIRE
		gameStage.mapper[6][20] = fire;
		gameStage.mapper[9][24] = fire;
		gameStage.mapper[9][23] = fire;
		gameStage.mapper[9][22] = fire;
		gameStage.mapper[12][13] = fire;
		gameStage.mapper[15][13] = fire;
		gameStage.mapper[18][34] = fire;
		copyObjects();
	}
}

/*
Method to draw the objects of the level passed as a parameter.

void drawObjects(int level){

	/*
	The following code will decide which level to draw game objects for. Such as the banana and the fire whenever called.
	
	

	if(level == 0){
		for(int i = 0; i < 22; i++){
			for(int j = 0; j< 20; j++){
				if(gameStage.copymap[i][j] == food){
					drawImage(j*32, i*32, &tilemap.images[food]);
					gameStage.mapper[i][j] = food;
				}
				if(gameStage.copymap[i][j]== fire){
					drawImage(j*32, i*32, &tilemap.images[fire]);
					gameStage.mapper[i][j] = fire;
				}
			}
		}
	}
	if(level == 1){
		for(int i = 0; i < 22; i++){
			for(int j = 0; j< 20; j++){
				if(gameStage.copymap[i][j] == food){
					drawImage(j*32, i*32, &tilemap.images[food]);
					gameStage.mapper[i][j] = food;
				}
				if(gameStage.copymap[i][j]== fire){
					drawImage(j*32, i*32, &tilemap.images[fire]);
					gameStage.mapper[i][j] = fire;
				}
			}
		}
	}
	if(level == 2){
		for(int i = 0; i < 22; i++){
			for(int j = 0; j< 20; j++){
				if(gameStage.copymap[i][j] == food){
					drawImage(j*32, i*32, &tilemap.images[food]);
					gameStage.mapper[i][j] = food;
				}
				if(gameStage.copymap[i][j]== fire){
					drawImage(j*32, i*32, &tilemap.images[fire]);
					gameStage.mapper[i][j] = fire;
				}
			}
		}
	}
	if(level == 3){
		for(int i = 0; i < 22; i++){
			for(int j = 0; j< 20; j++){
				if(gameStage.copymap[i][j] == food){
					drawImage(j*32, i*32, &tilemap.images[food]);
					gameStage.mapper[i][j] = food;
				}
				if(gameStage.copymap[i][j]== fire){
					drawImage(j*32, i*32, &tilemap.images[fire]);
					gameStage.mapper[i][j] = fire;
				}
			}
		}
	}
	if(level == 4){
		for(int i = 0; i < 22; i++){
			for(int j = 0; j< 20; j++){
				if(gameStage.copymap[i][j] == food){
					drawImage(j*32, i*32, &tilemap.images[food]);
					gameStage.mapper[i][j] = food;
				}
				if(gameStage.copymap[i][j]== fire){
					drawImage(j*32, i*32, &tilemap.images[fire]);
					gameStage.mapper[i][j] = fire;
				}
			}
		}
	}
}

/*
Method to update the lives displayed on the screen.
The paramter passed is the background so that the background is changed according to the current level

void lives(int background){
	for(int i = 0; i< 4; i++){
		drawImage(0, i*32, &tilemap.images[background]);
	}
	
	for(int i = 0; i < (gameStage.lives); i++){
		drawImage(0, i*32, &tilemap.images[heart]);
	}

		
}

/*
Method to copy the object locations of the main gameStage array to tthe copy array


void copyObjects(){
	for(int i = 0; i < 22; i++){
		for(int j = 0; j < 20; j++){
			gameStage.copymap[i][j] = gameStage.mapper[i][j];
		}
	}
}

/*
Method to draw the ending title screen after finish the game.

void drawEnd(){
	fillScreen(0xff0000);
	drawImage(490, 170, &tilemap.images[win]);
	drawImage(490, 500, &tilemap.images[button]);
	while(1){
		unsigned int result = read_snes();
		//Waits for any button press to break out of infinite loop and return to main Menu.
		if(result != MASK){
			break;
		}
	}
}
*/