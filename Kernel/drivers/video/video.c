
#include <stdint.h>
#include <color.h>
#include <defs.h>
#include <font.h>
#include <video.h>


struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed)); 

//Current positions
uint16_t x = 0, y = 0;

//Default color of the font
Color defaultColor = {0x7F, 0x7F, 0x7F};

typedef struct vbe_mode_info_structure VBEModeInfoBlock;
static VBEModeInfoBlock * screen_data = (void *)0x5C00;


//The data type of the coordinates is according to the size of the screen
//Return the address of the xy position 
void * getPosToPrint(uint16_t x, uint16_t y){
	//The 3 is because there is a difference of 3 addresses of 8bits each one for the colors. I mean we have a pixel every 3 bytes. 
	return (void *) (screen_data->framebuffer + 3 * (x + (y * screen_data->width)));
}

boolean checkValidPos(uint16_t x, uint16_t y){
	return x>=screen_data->width || y>=screen_data->height; 
}

void putPixel(uint16_t x, uint16_t y, Color color){
	if(checkValidPos(x,y) == true){
		return;
	}
	//I get the position of the buffer
	Color * pos = (Color *) getPosToPrint(x, y);
	//Print moment
	*pos = color;
}


void printChar(char c) {
    if (c == '\n') {
        //scr_printNewline();
        return;
    }

    if (c >= FIRST_CHAR && c <= LAST_CHAR) {
	    const char* data = font + 32*(c-33);
	    for (int h=0; h<16; h++) {
    		Color* pos = (Color*)getPosToPrint(x, y+h);
    		if (*data & 0b00000001) pos[0] = defaultColor;
    		if (*data & 0b00000010) pos[1] = defaultColor;
    		if (*data & 0b00000100) pos[2] = defaultColor;
    		if (*data & 0b00001000) pos[3] = defaultColor;
    		if (*data & 0b00010000) pos[4] = defaultColor;
    		if (*data & 0b00100000) pos[5] = defaultColor;
    		if (*data & 0b01000000) pos[6] = defaultColor;
    		if (*data & 0b10000000) pos[7] = defaultColor;
    		data++;
    		if (*data & 0b00000001) pos[8] = defaultColor;
    		data++;
    	}
    }

    x += CHAR_WIDTH;
    //if (x > screen_data->width - CHAR_WIDTH)
        //scr_printNewline();
}