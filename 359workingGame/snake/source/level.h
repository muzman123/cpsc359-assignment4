struct Snake {
    int posx;
    int posy;

    int isShielded;
};

struct GameState{

    // Main coordinates map that has integer values indicationg different game objects
    int mapper[20][20];
    // Copy of main coordinates map.
    int copymap[20][20];

    int starti;
    int startj;

    // store lives
    int lives;
    // store currentLevel
    int currentLevel;
    // store number of bananas picked up
    int eggs;

    int ci;
    int cj;
    // Player score
    int score;

    // End coordinates of current level.
    int endi;
    int endj;

    struct Snake s;
};

extern struct GameState gameStage;

// Game state struct to access in execution of the game.

// FUNCTION DECLARATIONS FOR THOSE IN level.c

void drawLevel1();

void drawLevel2();

void drawLevel3();

void drawLevel4();

void drawLevel5();

int gamePaused();

int MainScreen();

void reset();

void initLevel(int level);

void drawObjects(int level);

void lives(int background);

void drawEnd();

void copyObjects();