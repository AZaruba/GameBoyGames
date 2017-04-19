#include <gb/gb.h>
//#include "structs.h"

#include "sprites/sabre.c"

UINT8 i; // global loop counter

/*
 * updates a given sprite relative to its first frame (frame 0)
 *
 * sprite - index of sprite in tile directory
 * data - where in VRAM the sprite's animation frames begins
 * size - how big the sprite is
 * frame - which frame it is (each frame of a sprite will be stored sequentially)
 * TODO: decide format for storing sprites (sprites 0-6 will be PC,
 * 7-8 will be sword and 9-10 will be projectiles)
 */
void updateSprite(UINT8 sprite, UINT8 data, UINT8 size, UINT8 frame) {
	// loop for every 8x8 tile in the sprite
	for (i = 0; i < size; i++) {
		// sprite data starts at sprite, each frame is length size
		set_sprite_tile(sprite + i, data + (size * frame) + i);
	}
}

// load sprites to the specified locations (WIP)
void loadSprites(spriteData * spritePtr, UINT8 vr, UINT8 tileCount, char* name) {
    set_sprite_data(vr, tileCount, name);
    //set_sprite_palette(0, 1, sabreCGB);


    updateSprite(0x00, 0x00, 0x02, 0x00);
    updateSprite(0x02, 0x04, 0x04, 0x00);

    move_sprite(0, spritePtr->x, spritePtr->y);
    move_sprite(1, spritePtr->x + 8, spritePtr->y);
    move_sprite(2, spritePtr->x, spritePtr->y + 8);
    move_sprite(3, spritePtr->x + 8, spritePtr->y + 8);
    move_sprite(4, spritePtr->x, spritePtr->y + 16);
    move_sprite(5, spritePtr->x + 8, spritePtr->y + 16);
    //set_sprite_prop(0,0);
    //set_sprite_prop(1,0);
    //set_sprite_prop(2,0);
    //set_sprite_prop(3,0);
    //set_sprite_prop(4,0);
    //set_sprite_prop(5,0);

}

/*
 * updates the position and data of the sprite (WIP)
 */
void updatePos(spriteData * ptr) {
	move_sprite(4, ptr->x, ptr->y + 16);
    move_sprite(5, ptr->x + 8, ptr->y + 16);
    move_sprite(2, ptr->x, ptr->y + 8);
    move_sprite(3, ptr->x + 8, ptr->y + 8);
    move_sprite(0, ptr->x, ptr->y);
    move_sprite(1, ptr->x + 8, ptr->y);
}
