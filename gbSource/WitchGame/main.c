#include <gb/gb.h>
#include <stdio.h>
#include "malloc.c"
#include "structs.h"
#include "spriteFunc.c"
#include "collision.c"

#include "bkgTiles/levelOne.c"
#include "bkgTiles/castle.c"
#include "bkgTiles/hud.c"
#include "bkgTiles/hudExample.c"

//#include "sprites/sabre.c"

UINT8 t; // global timing counter
UINT8 h; // which buttons are being held down?

/*
 * gathers user input and updates the position of the PC
 */
void userInput(spriteData * ptr, UINT8 timing) {
	if (!(joypad() & J_A)) { h = h & !(J_A); }

    if (joypad() & J_RIGHT && ptr->x < 153) {
        ptr->x++;
    }

    if (joypad() & J_LEFT && ptr->x > 7) {
    	ptr->x--;
    }
    if (joypad() & J_A && !(h & J_A) && (collision(ptr) & 0x01) && !(ptr->state & 0x01)) {
    	ptr->g = 2;
    	ptr->state = ptr->state | 0x01; // set state bit 1 to air
    	ptr->state = ptr->state | 0x03; // set state bit 2 to rising
    	h = h | J_A;
    }

    if (timing%1 == 0) {
        gravity(ptr, timing);
    }
    updatePos(ptr);
    delay(16);
}

// main function
void main(void) {

    spriteData * witch = malloc(sizeof(spriteData));
    witch->state = 0x00;
    witch->g = 0;
    witch->x = 31;
    witch->y = 63;

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
    t = 0;

    DISPLAY_ON;
    while(1) {
        userInput(witch, t);
        if (t == 60) { t = 0; }
        else { t++; }
    }
}