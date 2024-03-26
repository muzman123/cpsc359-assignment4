// ADAPTED FROM fb.c at https://github.com/isometimes/rpi4-osdev/tree/master/part5-framebuffer
// note: the resolution is very high and takes a long time to draw the whole screen!
// consider changing it :) 
// Modified by Mohamad Elzohbi to decrease the resolution, for CPSC 359 Winter 2024

#include "mbox.h"

unsigned int width, height, pitch;
unsigned char* framebuffer;

// the tags we will be using in our "email" 
#define MBOX_TAG_SET_PHYS_WIDTH_HEIGHT 0x00048003
#define MBOX_TAG_SET_VIRT_WIDTH_HEIGHT 0x00048004
#define MBOX_TAG_SET_VIRT_OFFSET 0x00048004
#define MBOX_TAG_SET_COLOR_DEPTH 0x00048005 // "bits per pixel"
#define MBOX_TAG_SET_PIXEL_ORDER 0x00048006 // sets rgb or bgr as pixel order for framebuffer
#define MBOX_TAG_ALLOC_FRAMEBUFFER 0x00040001 // allocate frame buffer
#define MBOX_TAG_GET_PITCH 0x00040008

#define PIXEL_ORDER_RGB 1
#define PIXEL_ORDER_BGR 0

void init_framebuffer()
{
    mbox[0] = 35*4; // Length of message in bytes
    mbox[1] = MBOX_REQUEST;

    mbox[2] = MBOX_TAG_SET_PHYS_WIDTH_HEIGHT; // Tag identifier
    mbox[3] = 8; // size of buffer (8 since 2 x 4 byte ints)
    mbox[4] = 8; // length of value
    mbox[5] = 1024; // Value(width)
    mbox[6] = 768; // Value(height)

    mbox[7] = MBOX_TAG_SET_VIRT_WIDTH_HEIGHT;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = 1024;
    mbox[11] = 768;

    mbox[12] = MBOX_TAG_SET_VIRT_OFFSET;
    mbox[13] = 8;
    mbox[14] = 8;
    mbox[15] = 0; // Value(x)
    mbox[16] = 0; // Value(y)

    mbox[17] = MBOX_TAG_SET_COLOR_DEPTH;
    mbox[18] = 4;
    mbox[19] = 4;
    mbox[20] = 32; // Bits per pixel

    mbox[21] = MBOX_TAG_SET_PIXEL_ORDER;
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = PIXEL_ORDER_RGB; // RGB

    mbox[25] = MBOX_TAG_ALLOC_FRAMEBUFFER;
    mbox[26] = 8;
    mbox[27] = 8;
    mbox[28] = 4096; // FrameBufferInfo.pointer (value will be set!)
    mbox[29] = 0;    // FrameBufferInfo.size (value will be set!)

    mbox[30] = MBOX_TAG_GET_PITCH;
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0; // Bytes per line

    mbox[34] = MBOX_TAG_LAST;

    // Check call is successful and we have a pointer with depth 32
    if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
        mbox[28] &= 0x3FFFFFFF; // Convert GPU address to ARM address
        width = mbox[10];       // Actual physical width
        height = mbox[11];      // Actual physical height
        pitch = mbox[33];       // Number of bytes per line
        framebuffer = (unsigned char *)((long)mbox[28]);
    }
}

void drawPixel(int x, int y, unsigned int color)
{
    int offs = (y * pitch) + (x * 4);
    *((unsigned int*)(framebuffer + offs)) = color; // deref pixel at address, store color code in it!
}

void fillScreen(unsigned int color)
{
    // for width, height
        // fill pixel

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            drawPixel(col, row, color);
        }
    }

}

// fill is a bool that decides if you fill in the color
void drawRect(int x1, int y1, int x2, int y2, unsigned int color, int fill)
{
    int y=y1;

    while (y <= y2) {
       int x=x1;
       while (x <= x2) {
        // conditionally render based on current color
	  if ((x == x1 || x == x2) || (y == y1 || y == y2)) drawPixel(x, y, color);
	  else if (fill) drawPixel(x, y, color);
          x++;
       }
       y++;
    }
}

/* FOR GIMP EXPORTED C SOURCE FILES this method handles it: it takes a pixel and converts rgba to argb*/
void drawImage(unsigned char * img, int width, int height, int offx, int offy) {
    unsigned int * img_buff = (unsigned int *) img; // each pixel is 4 bytes. So should offset by 4bytes in indexing and fetch 4 bytes in accessing value casting to (int *) would be ideal.
    for (int i = 0; i < width; i++) for (int j = 0; j < height; j++) {
        int x = i+offx;
        int y = j+offy;
        int rgba_color = img_buff[width*j + i];
        int argb_color = __builtin_bswap32(rgba_color); // match endianness by reversing lower 32 bits
        argb_color = (argb_color << 24) | (argb_color >> 8); // rgba argb
        drawPixel(x,y,argb_color);
    }
}

void drawSquare(int rowStart, int columnStart, int squareSize, unsigned int color)
{
    int row, column, rowEnd, columnEnd;
    unsigned int *pixel = framebuffer;


    // Calculate where the row and columns end
    rowEnd = rowStart + squareSize;
    columnEnd = columnStart + squareSize;

    // Draw the square row by row, from the top down
    for (row = rowStart; row < rowEnd; row++) {
	// Draw each pixel in the row from left to right
        for (column = columnStart; column < columnEnd; column++) {
	    // Draw the individual pixel by setting its
	    // RGB value in the frame buffer
            pixel[(row * width) + column] = color;
        }
    }
}

void drawCheckerboard(int numberOfRows, int numberOfColumns, int squareSize,
		       unsigned int color1, unsigned int color2)
{
    int i, j;

    // Draw the rows from the top down
    for (i = 0; i < numberOfRows; i++) {
	// Draw the squares for the evenly numbered rows
	if ((i % 2) == 0) {
	    // Draw alternating squares starting with the first color
	    for (j = 0; j < numberOfColumns; j += 2) {
		drawSquare(i * squareSize, j * squareSize, squareSize, color1);
		drawSquare(i * squareSize, (j + 1) * squareSize, squareSize, color2);
	    }
	}
	// Draw the squares for the oddly numbered rows
	else {
	    // Draw alternating squares starting with the second color
	    for (j = 0; j < numberOfColumns; j += 2) {
		drawSquare(i * squareSize, j * squareSize, squareSize, color2);
		drawSquare(i * squareSize, (j + 1) * squareSize, squareSize, color1);
	    }
	}
    }	    
}