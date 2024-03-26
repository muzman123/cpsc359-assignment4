extern unsigned int width, height, pitch;
extern unsigned char* framebuffer;
void init_framebuffer();
void drawPixel(int x, int y, unsigned int color);
void fillScreen(unsigned int color);
void drawRect(int x1, int y1, int x2, int y2, unsigned int color, int fill);
void drawImage(unsigned char * img, int width, int height, int offx, int offy);
void drawSquare(int rowStart, int columnStart, int squareSize, unsigned int color);
void drawSnake(int startX, int startY);
void drawCheckerboard(int numberOfRows, int numberOfColumns, int squareSize,
		       unsigned int color1, unsigned int color2);
void *updateSnakePos(int xOffset, int yOffset, int currentX, int currentY);