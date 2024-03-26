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
    g.snake.obstacle = 0;
    g.snake.platform = 0;
    g.snake.speed = 10;

}*/

void *clockie(void *id); // clock thread
void *updateSnakePos(void *param);
void snesStart();
struct gameState g;

void printarts(char *str) {
	uart_puts(str);
}

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

    return 0;*/
}

void snesStart() {
    initSNES();
    printarts("Please press a button\n");
    unsigned int * initbuttons;
    while(1)
    {
        printf("up pressed");
        initbuttons = read_SNES();
        printf("up pressed");
        checkState(initbuttons);
        /*if(printMessage(initbuttons)==false)
        {
            printarts("program is terminating...");
            return 0;

        }*/
        if(initbuttons[5] == 0)
        {
            
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
    }*/
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
    */
    drawRect(currentX, currentY, currentX + xOffset, currentY + yOffset, 0x00008000, 1);
}

/*void *clockie(void *id)
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