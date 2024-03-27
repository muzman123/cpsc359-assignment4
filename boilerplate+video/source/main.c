/*
#include "gpio.h"
#include "uart.h"
#include "framebuffer.h"
#include <pthread.h>
#include "snes.h"
#include <stdio.h>

#define NUM_VALUE_PACKS 6
#define NUM_OBJECTS 15

#define GAME_GRID_WIDTH 20
#define GAME_GRID_HEIGHT 20
#define X_PIXEL_SCALE 32
#define Y_PIXEL_SCALE 32
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
//#include "images/starts.h"


int snake_size = 32;
int appStart = 0;
int paused = 0;
int quit = 0;
int movF = 0; // which direction is the sanke moving in

struct object {
    int startx;
    int starty;
    int x;
    int y;
    int obstacle;
    int width;
    int length;
    int platform;
    int active;
    int direction;
    int speed;
};

struct map {
    char map[20][20];
    struct object obstacles[15];
    short int *backdropPtr;
};

struct gameState {
    struct map stages[4];
    int pause;
    int score; 
    int lives; 
    int time;
    int won;
    int lost;
    struct object snake;
};

/*void initGameState(struct gameState * g) {
    g.pause = 0;
    g.score = 0;
    g.lives = 3;
    g.time = 0;
    g.won = 0;
    g.lost = 0;
    g.snake.startx = 0;
    g.snake.starty = 0;
    g.snake.direction = 8;
#define CLO_REG     0x7E003004
    g.snake.obstacle = 0;
    g.snake.platform = 0;
    g.snake.speed = 10;

}

void *clockie(void *id); // clock thread
void *updateSnakePos(void *param);
void snesStart();
struct gameState g;

int main()
{
    
    g.pause = 0;
    g.score = 0;
    g.lives = 3;
    g.time = 0;
    g.won = 0;
    g.lost = 0;
    g.snake.startx = 0;
    g.snake.starty = 0;
    g.snake.direction = 8;
    g.snake.obstacle = 0;
    g.snake.platform = 0;
    g.snake.speed = 10;

    printarts("up pressed");
    init_framebuffer(); // You can use framebuffer, width, height and pitch variables available in framebuffer.h

    //drawImage(starts.pixel_data, starts.width, starts.height, 100, 100);

    drawCheckerboard(20,20,32, 0x00800000, 0x08000000);
    printarts("down pressed");
    drawSnake(0, 0);
    printarts("up pressed");
    snesStart();
    

    /*appStart = 1;
    pthread_t snesInput;
    pthread_t drawScreen;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int th = pthread_create(&snesInput, &attr, input, "1")

    return 0;
#define CLO_REG     0x7E003004
            pthread_t thread_id; 
            pthread_attr_t attr;
            int arguments[] = {10, 0, g.snake.x, g.snake.y};
            pthread_attr_init(&attr);
            pthread_create(&thread_id, &attr, updateSnakePos, arguments);
            //updateSnakePos(10, 0, g.snake.x, g.snake.y);
            g.snake.x += 10;
            
        }
        
    }
}

void drawSnake(int startX, int startY)
{
    int endX = startX + snake_size;
    int endY = startY + snake_size;
    /*for (startX; startX < endX; startX++)
    {
        for (startY; startY < endY; startY++)
        {
            drawRect(startX, startY, 32, 0x00008000);
        }
    }
    drawRect(0, 0, 32, 32, 0x00008000, 1);

}

void *updateSnakePos(int xOffset, int yOffset, int currentX, int currentY)
{
    int endX = currentX + snake_size + xOffset;
    int endY = currentY + snake_size + yOffset;
    /*for (currentX; currentX < endX; currentX++)
    {
        for (currentY; currentY < endY; currentY++)
        {
            drawPixel(currentX, currentY, 0x00008000);
        }
    }
    
    drawRect(currentX, currentY, currentX + xOffset, currentY + yOffset, 0x00008000, 1);
}

void *clockie(void *id)
{
        while(quit == 0){ // while game not quit
            while (appStart == 0){ //while game not started
                if(movF == 5 || movF == 6){ // pressing up or down
                    drawMainMenu(movF); //cycle betwee up and down
                    updateBoard();

                }
                else if (movF == 9){ //user made a selection pressed A button
                    appStart = getStart(); //start game
                    quit = getQuit();       // quit game
                    }

            }
        }
    }
    
*/




#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "framebuffer.h"
#include "uart.h"

/*#include "../resources/MainMenu.c"
#include "../resources/SelectionBvoid printarts(char *str) {
	uart_puts(str);
}
#include "../resources/2.c"
#include "../resources/3.c"
#include "../resources/4.c"
#include "../resources/5.c"
#include "../resources/6.c"
#include "../resources/7.c"
#include "../resources/8.c"
#include "../resources/9.c"
#include "../resources/Score.c"
#include "../resources/Moves.c"
#include "../resources/Time.c"
#include "../resources/WinScreen.c"
#include "../resources/LoseScreen.c"
#include "../resources/WaterBackground.c"
#include "../resources/GameBoard.c"
#include "../resources/Platform.c"
#include "../resources/Powerup.c"
*/

#define GPSEL0 0
#define GPSET0 7
#define GPCLR0 10
#define GPLEV0 13

#define CLK 11
#define LAT 9
#define DAT 10

#define CLO_REG     0x7E003004

#define GPIO_BASE   0xFE200000

#define INP_GPIO(g,p) *(g+((p)/10)) &= ~(7<<(((p)%10)*3))
#define OUT_GPIO(g,p) *(g+((p)/10)) |= (1<<(((p)%10)*3))

static unsigned *gpioPtr = (unsigned*) GPIO_BASE;

void printarts(char *str) {
	uart_puts(str);
}

void wait(int waitTime) {
    unsigned *clo = (unsigned*)CLO_REG;
    unsigned c = *clo + waitTime; // micro Secs
    while (c > *clo);
}

//Initialized GPIO lines
void initializeGPIO(unsigned int *gpio)
{
	INP_GPIO(gpio, CLK);
	OUT_GPIO(gpio, CLK);
	INP_GPIO(gpio, LAT);
	OUT_GPIO(gpio, LAT);
	INP_GPIO(gpio, DAT);
}

//Function for writing to latch
void writeLatch(int bit, unsigned int *gpio)
{
	if(bit == 0)
    	{
       		gpio[GPCLR0] = 1 << LAT;	//Sets latch bit to 0
    	}
    	else if(bit == 1)
    	{
        	gpio[GPSET0] = 1 << LAT;	//Sets latch bit to 1
    	}
}

//Function for writing to clock
void writeClock(int bit, unsigned int *gpio)
{
    	if(bit == 0)
    	{
        	gpio[GPCLR0] = 1 << CLK;	//Sets clock bit to 0
    	}
    	else if(bit == 1)
    	{
        	gpio[GPSET0] = 1 << CLK;	//Sets clock bit to 1
    	}
}

//Function for reading from data line
int readData(unsigned int *gpio)
{
    	return (gpio[GPLEV0] >> DAT) & 1;	//Reads bit from data line
}

//Function for printing which buttons are pressed
void printMessage(unsigned short code)
{
	//2D char array for names of each button pushed, max size 13 based on string size
	char buttonB[13] = "B";
	char buttonY[13] = "Y";
	char buttonSelect[13] = "Select";
	char buttonStart[13] = "Start";
	char buttonJpUp[13] = "Joy-pad UP";
	char buttonJpDown[13] = "Joy-pad DOWN";
	char buttonJpLeft[13] = "Joy-pad LEFT";
	char buttonJpRight[13] = "Joy-pad RIGHT";
	char buttonA[13] = "A";
	char buttonX[13] = "X";
	char buttonLeft[13] = "Left";
	char buttonRight[13] = "Right";

	char* buttonList[12] = {buttonB, buttonY, buttonSelect, buttonStart, buttonJpUp, buttonJpDown, buttonJpLeft, buttonJpRight, buttonA, buttonX, buttonLeft, buttonRight};
  	//printf("You have pressed %s\n", buttonList[code]);
}

//Function to read SNES buttons pushed
unsigned short readSNES(unsigned int *gpio)
{
	unsigned short buttons = 0b1111111111111111;	//Initialized variable for buttons pushed
   	while(buttons == 0b1111111111111111)		//While loop while buttons aren't pushed
    	{
        	int counter = 0;	//Counter

		writeClock(1, gpio);		//Setup of SNES lines
		writeLatch(1, gpio);
		wait(12);
		writeLatch(0, gpio);

        	while(counter < 16)	//Loop to iterate through data line
        	{
                	wait(6);
                	writeClock(0, gpio);
                	wait(6);
                	int value = readData(gpio);	//Gets data line bit value
                	if(value == 0)
                	{
				//Adds bit to buttons pushed variable
                        	unsigned short temp = ~(1 << counter);
				buttons &= temp;
                	}
                	writeClock(1, gpio);	//Writes 1 to clock

          	      	counter++;	//Iterates counter
        	}
    	}
	return buttons;
}

//Get button function
int getButton(unsigned int *gpio)
{
    initializeGPIO(gpio);
	unsigned short button;
	while(1)	//Loops until start is pushed
	{
		printarts("Please press a button\n");
		unsigned short code = readSNES(gpio);	//Gets series of bits for buttons pushed
		for(int i = 0; i < 12; i++)	//Iterates through bits sent from readSNES
		{
			int value = (code >> i) & 1;	//Gets bit of in i position
			if(value == 0)	//If button is pushed
			{
				button = i;	//Sets button pushed to index for printing
                printMessage(button);	//Prints button pushed
                return button;
			}
		}
	}
}


struct Tile {
	int x;
	int y;
};

struct Object {
	int x;
	int y;
	bool isPlatform;
	int velocity;
	int pixelPos;
	int length;
};

struct Stage {
	bool isWater;
	struct Tile board[20][20];
	struct Object objects[18];
	short int *imagePtr;

};
struct GameState {
	struct Stage stages[4];
	int score;
	int extraLives;
	int secondsRemaining;
	int movesRemaining;
	//clock_t startTime;
	bool gameOver;

	struct Object powerup;

	bool won;
	bool lost;
	
	struct Object snake;
};
void gameMenu();
void gameState();
void initializeGame();
void update();
int collisionDetection();
bool checkExit();
void *playerInput(void *params);
void gamePlay();
void *counter(void *params);
void clear();
void *draw(void *params);
bool powerupCollision();

struct GameState game;
int currentStage;
bool gameStart, paused, quit, startHighlighted, playAgain, waitOnPlayAgain, spawnPowerups;
int menuSelect, powerupTimer;

int main(int argc, char **argv)
{
	printarts("\nMain");
	printarts("\nGame menu");
    gameStart = false;
	paused = false;
	quit = false;
	playAgain = false;
	spawnPowerups = false;
	powerupTimer = 30;
	pthread_t inputThread;	//Thread for input
	pthread_t drawThread;	//Thread for graphics
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int tc = pthread_create(&inputThread, &attr, playerInput, "1");	//Creating thread for input
	if(tc)
	{
		//printf("ERROR creating input thread, %d\n", tc);	//Error checking thread creation
		exit(-1);
	}
	/*int dc = pthread_create(&drawThread, &attr, draw, "1");		//Creating thread for drawing
	if(dc)
	{
		printf("ERROR creating draw thread, %d\n", tc);		//Error checking thread creation
		exit(-1);
	}
	gamePlay();
	return 0;
    */
}

//Thread for player input
void *playerInput(void *params)	
{
	
	//GPIO initialization from project part 1
	initializeGPIO(gpioPtr);
	unsigned short button;
	startHighlighted = true;
	//Loop for program
	while(!quit)
	{
		//Loop for menu selection
		while(!gameStart && !quit)
		{
			printarts("Please press a button\n");
			unsigned short code = readSNES(gpioPtr);	//Gets series of bits for buttons pushed
			for(int i = 0; i < 12; i++)	//Iterates through bits sent from readSNES
			{
				int value = (code >> i) & 1;	//Gets bit of in i position
				if(value == 0)	//If button is pushed
				{
					button = i;	//Sets button pushed to index for printing
					printMessage(button);	//Prints button pushed
					if(button == 6)	//Left
					{
						startHighlighted = true;
					}
					if(button == 7)	//Right
					{
						startHighlighted = false;
					}
					if(button == 3)	//Start
					{
						gameStart = true;	//Starts game
					}
					if(button == 8)	//A
					{
						if(startHighlighted)
						{
							gameStart = true;	//Starts game
						}
						else
						{
							quit = true;	//Exits program
						}
					}
				}
			}
			wait(1000000);
		}
		//Loop for gameplay and game not paused
		while(gameStart && !paused && !game.gameOver && !quit)
		{
			printarts("Please press a button\n");
			unsigned short code = readSNES(gpioPtr);	//Gets series of bits for buttons pushed
			for(int i = 0; i < 12; i++)	//Iterates through bits sent from readSNES
			{
				int value = (code >> i) & 1;	//Gets bit of in i position
				if(value == 0)	//If button is pushed
				{
					button = i;	//Sets button pushed to index for printing
					printMessage(button);	//Prints button pushed
					switch(button)
					{
						case 3:		//Start
							//Pause game
							paused = true;
							break;
						case 4:		//Up
							//Move snake up
							printarts("\nSnake going up");
							if(game.snake.y > 0)			//Bounds protection to prevent seg fault
								game.snake.y = game.snake.y - 1;	//Decrements snake y value
							game.movesRemaining = game.movesRemaining - 1;	//Decrements remaining moves
							break;
						case 5:		//Down
							printarts("\nSnake going down");
							game.snake.y = game.snake.y + 1;	//Increments snake y value
							game.movesRemaining = game.movesRemaining - 1;	//Decrements remaining moves
							break;
						case 6:		//Left
							//Move snake left
							printarts("\nSnake going left");
							game.snake.x = game.snake.x - 1;	//Increments snake x value
							game.movesRemaining = game.movesRemaining - 1;	//Decrements remaining moves
							break;
						case 7:		//Right
							//Move snake right
							printarts("\nSnake going right");
							game.snake.x = game.snake.x + 1;	//Decrements snake x value
							game.movesRemaining = game.movesRemaining - 1;	//Decrements remaining moves
							break;
						default:
							break;
					}
				}
			}
			wait(100000);
		}
		wait(10000);
		while(paused && !game.gameOver && !quit)
		{	
			printarts("Please press a button\n");
			unsigned short code = readSNES(gpioPtr);	//Gets series of bits for buttons pushed
			for(int i = 0; i < 12; i++)	//Iterates through bits sent from readSNES
			{
				int value = (code >> i) & 1;	//Gets bit of in i position
				if(value == 0)	//If button is pushed
				{
					button = i;	//Sets button pushed to index for printing
					printMessage(button);	//Prints button pushed
					switch(button)
					{
						case 0:		//B
							break;
						case 1:		//Y
							break;
						case 2:		//Select
							break;
						case 3:		//Start
							//Unpause game
							paused = false;
							break;
						case 4:		//Up
							if(menuSelect == 1)
								menuSelect = 0;
							else if(menuSelect == 2)
								menuSelect = 1;
							break;
						case 5:		//Down
							if(menuSelect == 1)
								menuSelect = 2;
							else if(menuSelect == 0)
								menuSelect = 1;
							break;
						case 6:		//Left
							break;
						case 7:		//Right
							break;
						case 8:		//A
							if(menuSelect == 0)
								paused = false;
							else if(menuSelect == 1)
							{
								game.gameOver = true;
							}
							else
								quit = true;
							break;
						case 9:		//X
							break;
						case 10:	//Left bumper
							break;
						case 11:	//Right bumper
							break;
						default:
							break;
					}
				}
			}
			printarts("\nPAUSED");
			wait(100000);
		}
		while(game.gameOver)
		{
			unsigned short code = readSNES(gpioPtr);	//Gets series of bits for buttons pushed
			for(int i = 0; i < 12; i++)	//Iterates through bits sent from readSNES
			{
				int value = (code >> i) & 1;	//Gets bit of in i position
				if(value == 0)	//If button is pushed
				{
					waitOnPlayAgain = false;
					playAgain = true;
				}
			}
		}
	}
	pthread_exit(NULL);
}


//Initializes variables needed for game
void initializeGame()
{
	time_t t;
	//srand((unsigned) time(&t));

	printarts("\nInit game");
	//game.startTime = clock();
	game.score = 0;
	game.extraLives = 4;
	game.secondsRemaining = 999;
	game.movesRemaining = 200;
	game.gameOver = false;
	game.won = false;
	game.lost = false;
	currentStage = 0;
	menuSelect = 0;

	game.snake.x = 10;
	game.snake.y = 20;

	//Initializes game objects
	for(int i = 0; i < 4; i++)
	{
		int temp = -1;	//Temp is for reversing velocities of objects
		for(int j = 0; j < 18; j++)
		{
			for(int a = 0; a < 20; a++)
			{
				for(int b = 0; b < 20; b++)
				{
					game.stages[i].board[a][b].x = b;
					game.stages[i].board[a][b].y = a;
                }
			}
			game.stages[i].objects[j].x = 0;
			game.stages[i].objects[j].y = j + 2;
			game.stages[i].objects[j].velocity = temp*10 % 3;		//TODO: Might change object velocities later
			game.stages[i].objects[j].length = 1;
			temp = -temp;
		}
		game.stages[i].isWater = i%2;
	}
	//Game Stage 0
	/*game.stages[0].isWater = false;
	game.stages[0].imagePtr = (short int *) Car.pixel_data;


	//Game Stage 1
	game.stages[1].isWater = true;
	game.stages[1].imagePtr = (short int *) Turtle.pixel_data;
	for(int j = 0; j < 18; j++)
		game.stages[1].objects[j].length = 3;

	//Game Stage 2
	game.stages[2].isWater = false;
	game.stages[2].imagePtr = (short int *) Car2.pixel_data;


	//Game Stage 3
	game.stages[3].isWater = true;
	game.stages[3].imagePtr = (short int *) Platform.pixel_data;
	for(int j = 0; j < 18; j++)
		game.stages[3].objects[j].length = 3;
        */
}

//Function for game
void gamePlay()
{
	while(!quit)
	{
		printarts("\nGamePlay");
		initializeGame();
		bool exit = false;
		while(!exit && !quit)
		{
			if(gameStart)
			{
				update();
				exit = checkExit();
				wait(1000);
			}
		}
		wait(10000);
		while(waitOnPlayAgain && !quit);
		if(playAgain == true)
		{
			gameStart = false;
			paused = false;
			quit = false;
			playAgain = false;
			spawnPowerups = false;
			powerupTimer = 30;
		}
	}
}

void update()
{
	//printf("\nUpdate");
	//printf("\nSnake y: %i Snake x: %i", game.snake.y, game.snake.x);
	//clock_t currentTime = clock();		//Gets current time in ticks
	//int timePassed = (currentTime - game.startTime) / CLOCKS_PER_SEC;	//Converts ticks into seconds
	/*if(timePassed >= powerupTimer && !spawnPowerups)
	{
		time_t t;
		//srand((unsigned) time(&t));
		game.powerup.x = (6 % 15) + 2;
		game.powerup.y = (7 % 15) + 2;
		spawnPowerups = true;
	}
	game.secondsRemaining = 999 - timePassed;		//Seconds remaining calculation
    */
	int collide = collisionDetection();	
	//Adds platform velocity to snake
	if(collide != -1 && game.stages[currentStage].isWater)	//If stage is water then objects are platforms
	{
		game.snake.x = game.snake.x + game.stages[currentStage].objects[collide].velocity;
	}
	//If snake is out of bounds, or dies
	else if((collide != -1 && !game.stages[currentStage].isWater) || (game.stages[currentStage].isWater && collide == -1 && game.snake.y > 1 && game.snake.y < 20))
	{
		game.extraLives = game.extraLives - 1;
		game.snake.x = 10;
		game.snake.y = 20;
	}

	//Adds velocity to objects, resets them when they hit the edge
	for(int i = 0; i < 18; i++)
	{
		//Adds for pixel effect of moving per pixel
		for(int j = 0; j < 32; j++)
		{
			game.stages[currentStage].objects[i].pixelPos = j;
			wait(1000);
		}
		//Object bounds detection to loop them across the screen
		game.stages[currentStage].objects[i].x = game.stages[currentStage].objects[i].x + game.stages[currentStage].objects[i].velocity;
		if(game.stages[currentStage].objects[i].x < 0)
		{
			game.stages[currentStage].objects[i].x = 20;
		}
		if(game.stages[currentStage].objects[i].x > 20)
		{
			game.stages[currentStage].objects[i].x = 0;
		}
	}
	//Bounds detection for snake
	if(game.snake.x < 0 || game.snake.x > 20 || game.snake.y > 20)
	{
		game.extraLives = game.extraLives - 1;
		game.snake.x = 10;
		game.snake.y = 20;
	}
	//Checks if snake completed stage
	if(game.snake.y <= 0)
	{
		currentStage = currentStage + 1;
		game.snake.y = 20;
        //printf("\nGoing up a stage");
	}
	
	if(powerupCollision())
	{
		spawnPowerups = false;
		powerupTimer = powerupTimer + powerupTimer;
		game.powerup.x = 0;
		game.powerup.y = 0;
		game.movesRemaining = game.movesRemaining + 100;
	}

	//Score calculation
	game.score = game.secondsRemaining + game.movesRemaining + (game.extraLives * 100);

	//printf("\n\nData\nTime remaining: %i\nLives: %i\nMoves: %i\n", game.secondsRemaining, game.extraLives, game.movesRemaining);
}

typedef struct {
	short int color;
	int x, y;
} Pixel;

//struct fbs framebufferstruct;
void drawPixel(int x, int y, unsigned int color);

/*
void *draw(void *params)
{

	framebufferstruct = initFbInfo();
	
	short int *backgroundPtr=(short int *) Background.pixel_data;	
	short int *mainMenuPtr=(short int *) Menu.pixel_data;	
	short int *pauseMenuPtr=(short int *) Pause.pixel_data;	
	short int *selectionBarPtr=(short int *) SelectionBar.pixel_data;	
	short int *carPtr=(short int *) Car.pixel_data;
	short int *logPtr=(short int *) Log.pixel_data;
	short int *turtlePtr=(short int *) Turtle.pixel_data;
	short int *snakePtr=(short int *) Snake.pixel_data;
	short int *zeroPtr=(short int *) Zero.pixel_data;
	short int *onePtr=(short int *) One.pixel_data;
	short int *twoPtr=(short int *) Two.pixel_data;
	short int *threePtr=(short int *) Three.pixel_data;
	short int *fourPtr=(short int *) Four.pixel_data;
	short int *fivePtr=(short int *) Five.pixel_data;
	short int *sixPtr=(short int *) Six.pixel_data;
	short int *sevenPtr=(short int *) Seven.pixel_data;
	short int *eightPtr=(short int *) Eight.pixel_data;
	short int *ninePtr=(short int *) Nine.pixel_data;
	short int *scorePtr=(short int *) Score.pixel_data;
	short int *movesPtr=(short int *) Moves.pixel_data;
	short int *timePtr=(short int *) Time.pixel_data;
	short int *winPtr=(short int *) Win.pixel_data;
	short int *losePtr=(short int *) Lose.pixel_data;
	short int *gameBoardPtr=(short int *) GameBoard.pixel_data;
	short int *waterPtr=(short int *) Water.pixel_data;
	short int *powerupPtr=(short int *) Powerup.pixel_data;

	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int i = 0;

	while(!quit)
	{
		while(!gameStart && !game.gameOver && !quit)
		{
			i=0;
			for (int y = 0; y < 640; y++)
			{
				for (int x = 0; x < 640; x++) 
				{	
						pixel->color = mainMenuPtr[i]; 
						pixel->x = x;
						pixel->y = y;
							
						drawPixel(pixel);
						i++;		
				}
			}

			if(startHighlighted)
			{
				i = 0;
				for (int y = 0; y < 10; y++)
				{
					for (int x = 0; x < 280; x++) 
					{
						pixel->color = selectionBarPtr[i]; 
						pixel->x = x;
						pixel->y = y + 450;
							
						drawPixel(pixel);
						i++;		
					}
				}
			}
			else
			{
				i = 0;
				for (int y = 0; y < 10; y++)
				{
					for (int x = 0; x < 280; x++) 
					{
						pixel->color = selectionBarPtr[i]; 
						pixel->x = x + 320;
						pixel->y = y + 450;
							
						drawPixel(pixel);
						i++;		
					}
				}
			}
		}
		while(gameStart && !paused && !game.gameOver && !quit)
		{
			wait(10000);
			i = 0;
			for (int y = 0; y < 720; y++)
			{
				for (int x = 0; x < 720; x++) 
				{	
					pixel->color = gameBoardPtr[i];
					pixel->x = x;
					pixel->y = y;

					drawPixel(pixel);
					i++;		
				}
			}
			if(game.stages[currentStage].isWater)
			{
				i = 0;
				for (int y = 0; y < 640; y++)
				{
					for (int x = 0; x < 640; x++) 
					{	
						pixel->color = waterPtr[i];
						pixel->x = x;
						pixel->y = y + 68;

						drawPixel(pixel);
						i++;		
					}
				}
			}
			else if(!game.stages[currentStage].isWater)
			{
				i = 0;
				for (int y = 
				0; y < 640; y++)
				{
					for (int x = 0; x < 640; x++) 
					{	
						pixel->color = backgroundPtr[i];
						pixel->x = x;
						pixel->y = y + 68;

						drawPixel(pixel);
						i++;		
					}
				}
			}
			for(int j = 0; j < 18; j++)	//OBJECTS
			{
				for(int k = 0; k < game.stages[currentStage].objects[j].length; k++)
				{
					i = 0;
					for (int y = 0; y < 32; y++)
					{
						for (int x = 0; x < 32; x++) 
						{	
							pixel->color = game.stages[currentStage].imagePtr[i]; 
							pixel->x = x + (game.stages[currentStage].objects[j].x * 32) + game.stages[currentStage].objects[j].pixelPos + k*32;	//Update locations for objects
							pixel->y = y + (game.stages[currentStage].objects[j].y * 32) + 68;
							
							drawPixel(pixel);
							i++;						
						}
					}
				}
			}
			//Drawing snake
			i = 0;
			for (int y = 0; y < 32; y++)
			{
				for (int x = 0; x < 32; x++) 
				{	
					pixel->color = snakePtr[i]; 
					pixel->x = x + (game.snake.x * 32);
					pixel->y = y + (game.snake.y * 32) + 68;
					
					drawPixel(pixel);
					i++;			
				}
			}

			//Drawing powerup
			if(spawnPowerups)
			{
				i = 0;
				for (int y = 0; y < 32; y++)
				{
					for (int x = 0; x < 32; x++) 
					{	
						pixel->color = powerupPtr[i]; 
						pixel->x = x + (game.powerup.x * 32);
						pixel->y = y + (game.powerup.y * 32) + 68;
						
						drawPixel(pixel);
						i++;			
					}
				}
			}

			//Drawing extra lives
			for(int j = 0; j < game.extraLives; j++)
			{
				i = 0;
				for (int y = 0; y < 32; y++)
				{
					for (int x = 0; x < 32; x++) 
					{	
						pixel->color = snakePtr[i]; 
						pixel->x = x + 32*j;
						pixel->y = y;
						
						drawPixel(pixel);
						i++;			
					}
				}
			}

			
			//Print score here
			i = 0;
			for (int y = 0; y < 32; y++)
			{
				for (int x = 0; x < 110; x++) 
				{	
					pixel->color = scorePtr[i]; 
					pixel->x = x + 160;
					pixel->y = y;
					
					drawPixel(pixel);
					i++;			
				}
			}
			int temp = game.score;		//Temp pointer for the number pointer
			short int *tempPtr;
			for(int j = 4; j > 0; j--)
			{
				i = 0;
				int num = temp % 10;
				switch(num)
				{
					case 0:
						tempPtr = zeroPtr;
						break;
					case 1:
						tempPtr = onePtr; 
						break;
					case 2:
						tempPtr = twoPtr; 
						break;
					case 3:
						tempPtr = threePtr; 
						break;
					case 4:
						tempPtr = fourPtr; 
						break;
					case 5:
						tempPtr = fivePtr; 
						break;
					case 6:
						tempPtr = sixPtr; 
						break;
					case 7:
						tempPtr = sevenPtr; 
						break;
					case 8:
						tempPtr = eightPtr; 
						break;
					case 9:
						tempPtr = ninePtr; 
						break;
				}
				temp = temp / 10;
				for (int y = 0; y < 32; y++)
				{
					for (int x = 0; x < 32; x++) 
					{	
						pixel->color = tempPtr[i];
						pixel->x = x + 32*j + 230;
						pixel->y = y;
						
						drawPixel(pixel);
						i++;			
					}
				}
			}
			i = 0;
			for (int y = 0; y < 32; y++)
			{
				for (int x = 0; x < 100; x++) 
				{	
					pixel->color = timePtr[i]; 
					pixel->x = x + 400;
					pixel->y = y;
					
					drawPixel(pixel);
					i++;			
				}
			}
			//Print time here
			temp = game.secondsRemaining;
			for(int j = 3; j > 0; j--)
			{
				i = 0;
				int num = temp % 10;
				switch(num)
				{
					case 0:
						tempPtr = zeroPtr;
						break;
					case 1:
						tempPtr = onePtr; 
						break;
					case 2:
						tempPtr = twoPtr; 
						break;
					case 3:
						tempPtr = threePtr; 
						break;
					case 4:
						tempPtr = fourPtr; 
						break;
					case 5:
						tempPtr = fivePtr; 
						break;
					case 6:
						tempPtr = sixPtr; 
						break;
					case 7:
						tempPtr = sevenPtr; 
						break;
					case 8:
						tempPtr = eightPtr; 
						break;
					case 9:
						tempPtr = ninePtr; 
						break;
				}
				temp = temp / 10;
				for (int y = 0; y < 32; y++)
				{
					for (int x = 0; x < 32; x++) 
					{	
						pixel->color = tempPtr[i];
						pixel->x = x + 32*j + 510;
						pixel->y = y;
						
						drawPixel(pixel);
						i++;			
					}
				}
			}
			i = 0;
			for (int y = 0; y < 32; y++)
			{
				for (int x = 0; x < 120; x++) 
				{	
					pixel->color = movesPtr[i]; 
					pixel->x = x;
					pixel->y = y + 32;
					
					drawPixel(pixel);
					i++;			
				}
			}
			//Print moves here
			temp = game.movesRemaining;
			for(int j = 3; j > 0; j--)
			{
				i = 0;
				int num = temp % 10;
				switch(num)
				{
					case 0:
						tempPtr = zeroPtr;
						break;
					case 1:
						tempPtr = onePtr; 
						break;
					case 2:
						tempPtr = twoPtr; 
						break;
					case 3:
						tempPtr = threePtr; 
						break;
					case 4:
						tempPtr = fourPtr; 
						break;
					case 5:
						tempPtr = fivePtr; 
						break;
					case 6:
						tempPtr = sixPtr; 
						break;
					case 7:
						tempPtr = sevenPtr; 
						break;
					case 8:
						tempPtr = eightPtr; 
						break;
					case 9:
						tempPtr = ninePtr; 
						break;
				}
				temp = temp / 10;
				for (int y = 0; y < 32; y++)
				{
					for (int x = 0; x < 32; x++) 
					{	
						pixel->color = tempPtr[i];
						pixel->x = x + 32*j + 130;
						pixel->y = y + 32;
						
						drawPixel(pixel);
						i++;			
					}
				}
			}
		}
		while(paused && !game.gameOver && !quit)
		{
			i = 0;
			for (int y = 0; y < 640; y++)
			{
				for (int x = 0; x < 640; x++) 
				{	
						pixel->color = pauseMenuPtr[i]; 
						pixel->x = x + 40;
						pixel->y = y + 40;
						
						drawPixel(pixel);
						i++;			
				}
			}
			
			i = 0;
			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 280; x++) 
				{
					pixel->color = selectionBarPtr[i]; 
					pixel->x = x + 160;
					pixel->y = y + 250 + (100*menuSelect);
						
					drawPixel(pixel);
					i++;		
				}
			}
		}
		wait(10000);
		while(waitOnPlayAgain && !quit)
		{
			i = 0;
			for (int y = 0; y < 720; y++)
			{
				for (int x = 0; x < 720; x++) 
				{	
						if(game.won)
							pixel->color = winPtr[i];
						else if(game.lost)
							pixel->color = losePtr[i];
						pixel->x = x;
						pixel->y = y;
						
						drawPixel(pixel);
						i++;			
				}
			}
		}
	}
	// free pixel's allocated memory 
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);

	pthread_exit(NULL);
}

// void drawPixel(Stage *stage)
// {
// 	memcpy(framebufferstruct.fptr, stage, 1280*720*2);
// }

//Draw a pixel 
void drawPixel(Pixel *pixel){
	long int location = (pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}
*/


//Checks snake position against object positions for current stage, returns object position in list
int collisionDetection()
{
	//Checks object x with snake x and object y with snake y
	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < game.stages[currentStage].objects[i].length; j++)
		{
			if(game.stages[currentStage].objects[i].x == game.snake.x && game.stages[currentStage].objects[i].y == game.snake.y)
				return i;
		}
	}
	return -1;
}

bool powerupCollision()
{
	if(game.powerup.x == game.snake.x && game.powerup.y == game.snake.y)
		return true;
	return false;
}

//Checks to see if game is over via snake reaching castle or running out of live/moves/time
bool checkExit()
{
	if(currentStage >= 3 && game.snake.y <= 0)
	{
		//WIN
        printarts("\nCongrats you have won");
		game.lost = false;
		game.won = true;
		game.gameOver = true;
		waitOnPlayAgain = true;
		return true;
	}
	if(game.extraLives == 0 || game.movesRemaining == 0 || game.secondsRemaining == 0 || game.gameOver)
	{
		//LOSE
        printarts("\nSorry you lose");
		game.won = false;
		game.lost = true;
		game.gameOver = true;
		waitOnPlayAgain = true;
		return true;
	}
	return false;
}
