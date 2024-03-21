
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
    object obstacles[15];
    short int *backdropPtr;
};

struct gameState {
    map stages[4];
    int pause;
    int score;
    int lives;
    int time;
    int won;
    int lost;
    object snake;

};