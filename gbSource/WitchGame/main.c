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
UINT8 *gr; // gravity timer
UINT8 h; // which buttons are being held down?
UINT8 vr; // how far along VRAM are we?
unsigned char *collider; // pointer where we store background tiles for collision

/*
 * gathers user input and updates the position of the PC
 */
void userInput(spriteData * ptr, UINT8 timing) {
	// make sure A isn't being held down (cancels Bunny hopping)
	if (!(joypad() & J_A)) { h = h & !(J_A); }

    // move right and update state to face right
    if (joypad() & J_RIGHT && ptr->x < 153) {
    	// if we change direction, change sprite
    	if (ptr->state & 0x08) {
            updateSprite(0x00, 0x00, 0x02, 0x00);
            updateSprite(0x02, 0x04, 0x04, 0x00);
    	}

        // walking animation on ground
        if ((collision(ptr, collider) & 0x01)) {
            if (timing%30 == 0) {
        	    updateSprite(0x02, 0x04, 0x04, 0x01);
            } else if (timing%30 == 15) {
                updateSprite(0x02, 0x04, 0x04, 0x02);
            }
        }

    	ptr->state = ptr->state & 0xF7;
        ptr->x++;
    }

    // move left and update state to face left
    if (joypad() & J_LEFT && ptr->x > 7) {
    	// if we change direction, change sprite
    	if (!(ptr->state & 0x08)) {
            updateSprite(0x00, 0x00, 0x02, 0x01);
            updateSprite(0x02, 0x04, 0x04, 0x05);
    	}

 	   // walking animation on ground
    	if ((collision(ptr, collider) & 0x01)) {
        	if (timing%30 == 0) {
        		updateSprite(0x02, 0x04, 0x04, 0x06);
     	   } else if (timing%30 == 15) {
        	    updateSprite(0x02, 0x04, 0x04, 0x07);
       	 }
    }	

    	ptr->state = ptr->state | 0x08;
    	ptr->x--;
    }

    // jump IFF grounded and A is pressed while not held
    if (joypad() & J_A && !(h & J_A) && (collision(ptr) & 0x01) && !(ptr->state & 0x01)) {
    	ptr->g = 8;
    	ptr->state = ptr->state | 0x01; // set state bit 1 to air
    	ptr->state = ptr->state | 0x03; // set state bit 2 to rising
    	h = h | J_A;
    }


    // handle gravity only on some frames (as it is VERY fast at 60hz)
    if (timing%1 == 0) {
        gravity(ptr, collider, gr);
    }
    updatePos(ptr);
    delay(16);
}

// main function
void main(void) {
    spriteData * witch = malloc(sizeof(spriteData));
    collider = malloc(sizeof(unsigned char));
    gr = malloc(sizeof(UINT8));

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
    loadSprites(witch, vr, 0x29, sabre);
    vr = vr + 0x2F;

    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;
    t = 0;
    vr = 0;

    DISPLAY_ON;
    while(1) {
        userInput(witch, t);
        if (t == 60) { t = 0; }
        else { t++; }
    }
}