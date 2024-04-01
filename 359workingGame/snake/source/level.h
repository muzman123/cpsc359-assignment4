
// snake struct
struct Snake {
    int posx;
    int posy;

    int speed;
    int isShielded;
};

struct GameState{

    // map that stores info of what type of object each coord in the map has
    int mapper[20][20];
    // start coords
    int startx;
    int starty;
    // coord of bat
    int batPosX;
    int batPosY;

    int eggsEaten;
    //time ingame
    int time;
    // store lives
    int lives;
    // store currentLevel
    int currentLevel;
    // player score
    int score;
    // finish coords
    int finX;
    int finY;

    struct Snake s;
};

extern struct GameState gameStage;


void drawLevel1();

void drawLevel2();

/*void drawLevel3();

void drawLevel4();

void drawLevel5();

int MainScreen();

void reset();

void initLevel(int level);

void drawObjects(int level);

void lives(int background);

void drawEnd();

void copyObjects();
*/
void initGameState();

void updateTime();

void updateScore();

void updateLives();

void drawExtraLives();

void drawSpeedBoost();

void updateBatPos();