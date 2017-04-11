#include <gb/gb.h>
#include <stdio.h>

#include "bkgTiles/levelOne.c"
#include "bkgTiles/castle.c"
#include "bkgTiles/hud.c"
#include "bkgtiles/hudExample.c"

#include "sprites/sabre.c"
int i;
void updateSprite(UINT8 sprite, UINT8 data, UINT8 size, UINT8 frame) {
	// loop for every 8x8 tile in the sprite
	for (i = 0; i < size; i++) {
		// sprite data starts at sprite, each frame is length size
		set_sprite_tile(sprite + i, data + (size * frame) + i);
	}
}

void main(void) {
	wait_vbl_done();
  SPRITES_8x8;
  DISPLAY_OFF;

  // load sprites with color (hopefully)
  set_sprite_data(0,0,sabre);
  set_sprite_palette(0,1, sabreCGB);
  set_bkg_palette(1, 1, sabreCGB);

  // set up HUD
  move_win(7, 128);
  set_win_data(0x15, 0x05, hud);
  set_win_tiles(0x00, 0x00, 0x14, 0x02, hudExample);

  // set up background
  set_bkg_data(0x00, 0x14, castle);
  set_bkg_tiles(0x00, 0x00, 0x14, 0x10, levelOne);

  updateSprite(0x00, 0x00, 0x02, 0x00);
  updateSprite(0x02, 0x04, 0x04, 0x00);

  move_sprite(0, 75, 75);
  move_sprite(1, 75 + 8, 75);
  move_sprite(2, 75, 75 +8);
  move_sprite(3, 75 + 8, 75 +8);
  move_sprite(4, 75, 75 + 16);
  move_sprite(5, 75 + 8, 75 + 16);

  set_sprite_prop(0,0);
  set_sprite_prop(1,0);
  set_sprite_prop(2,0);
  set_sprite_prop(3,0);
  set_sprite_prop(4,0);
  set_sprite_prop(5,0);

  SHOW_BKG;
  SHOW_WIN;
  SHOW_SPRITES;

  DISPLAY_ON;
  while(1) { 

  }
}