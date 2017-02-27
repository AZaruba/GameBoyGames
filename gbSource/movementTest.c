#include <gb/gb.h>
#include <stdio.h>
#include "malloc.c"

#include "bkgTiles/levelOne.c"
#include "bkgTiles/castle.c"
#include "bkgTiles/hud.c"
#include "bkgTiles/hudExample.c"

#include "sprites/sabre.c"

typedef struct {
    UINT8 x;
    UINT8 y;
    INT8 g;
    UINT8 state;
} spriteData;

UINT8 i; // global loop integer

/*
 * loads player sprite
 */
void loadSprites(spriteData * spritePtr) {
    set_sprite_data(0x00, 0x0C, sabre);
    set_sprite_tile(0x00, 0x00);
    set_sprite_tile(0x01, 0x01);
    set_sprite_tile(0x02, 0x02);
    set_sprite_tile(0x03, 0x03);
    set_sprite_tile(0x04, 0x04);
    set_sprite_tile(0x05, 0x05);

    move_sprite(4, spritePtr->x, spritePtr->y + 16);
    move_sprite(5, spritePtr->x + 8, spritePtr->y + 16);
    move_sprite(2, spritePtr->x, spritePtr->y + 8);
    move_sprite(3, spritePtr->x + 8, spritePtr->y + 8);
    move_sprite(0, spritePtr->x, spritePtr->y);
    move_sprite(1, spritePtr->x + 8, spritePtr->y);
}

/*
 * updates the position of the PC
 */
void updatePos(spriteData * ptr) {
	move_sprite(4, ptr->x, ptr->y + 16);
    move_sprite(5, ptr->x + 8, ptr->y + 16);
    move_sprite(2, ptr->x, ptr->y + 8);
    move_sprite(3, ptr->x + 8, ptr->y + 8);
    move_sprite(0, ptr->x, ptr->y);
    move_sprite(1, ptr->x + 8, ptr->y);
}

/*
 * checks collision between player character and various objects
 */
UINT8 collision(spriteData * ptr) {
	UINT8 edges = 0x00;
	if (ptr->y <= 112) {
		ptr->y = 112;
		edges += 0x01;
	}
	return edges;
}

void gravity(spriteData * ptr) {
    if ((collision(ptr) & 0x01) && ptr->g <= 0) {
    	ptr->g = 0;
    	return;
    }
    else {
    	if (ptr->g > -2) {
    	    ptr->g--;
    	}
    	ptr->y = ptr->y - ptr->g;
    }
}

/*
 * gathers user input and updates the position of the PC
 */
void userInput(spriteData * ptr) {

    if (joypad() & J_RIGHT && ptr->x < 153) {
        ptr->x++;
    }

    if (joypad() & J_LEFT && ptr->x > 7) {
    	ptr->x--;
    }
    if (joypad() & J_A  && (collision(ptr) & 0x01) ) {
    	ptr->g = 5;
    }
    gravity(ptr);
    updatePos(ptr);
    delay(16);
}

void main(void) {
	// allocate space for sprite position information
    spriteData * witch = malloc(sizeof(spriteData));
    witch->state = 0x00;
    witch->g = 0;
    witch->x = 31;
    witch->y = 40;

    // pre-start prep
	wait_vbl_done();
    SPRITES_8x8;
   	DISPLAY_OFF;

   	// load background data
    set_bkg_data(0x00,0x14, castle);
    set_bkg_tiles(0x00, 0x00, 0x14, 0x10, levelOne);

    // set up HUD window
    move_win(7,128);
    set_win_data(0x14,0x05, hud);
    set_win_tiles(0x00,0x00, 0x14, 0x02, hudExample);

    // load sprites
    loadSprites(witch);

    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;

    DISPLAY_ON;

    while(1) {
        userInput(witch);

    }
}