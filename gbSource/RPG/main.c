#include <gb/gb.h>
#include "malloc.c"

#include "Sprites/jerd.c"
#include "Sprites/jirard.c"
#include "winTiles/hud.c"
#include "winTiles/hudEx.c"
#include "bkgTiles/bkg.c"
#include "bkgTiles/bkgEx.c"

void loadSprites() {
	set_sprite_data(0x00, 0x06, jerd);
	set_sprite_data(0x06, 0x06, jirard);

	set_sprite_tile(0x00, 0x00);
	set_sprite_tile(0x01, 0x01);
	set_sprite_tile(0x02, 0x02);
	set_sprite_tile(0x03, 0x03);
	set_sprite_tile(0x04, 0x04);
	set_sprite_tile(0x05, 0x05);

	set_sprite_tile(0x06, 0x06);
	set_sprite_tile(0x07, 0x07);
	set_sprite_tile(0x08, 0x08);
	set_sprite_tile(0x09, 0x09);
	set_sprite_tile(0x0A, 0x0A);
	set_sprite_tile(0x0B, 0x0B);

	move_sprite(0x00, 144, 24 + 16);
	move_sprite(0x01, 152, 24 + 16);
	move_sprite(0x02, 144, 32 + 16);
	move_sprite(0x03, 152, 32 + 16);
	move_sprite(0x04, 144, 40 + 16);
	move_sprite(0x05, 152, 40 + 16);

	move_sprite(0x06, 144, 48 + 24);
	move_sprite(0x07, 152, 48 + 24);
	move_sprite(0x08, 144, 56 + 24);
	move_sprite(0x09, 152, 56 + 24);
	move_sprite(0x0A, 144, 64 + 24);
	move_sprite(0x0B, 152, 64 + 24);

	set_sprite_prop(0x00,0);
    set_sprite_prop(0x01,0);
    set_sprite_prop(0x02,0);
    set_sprite_prop(0x03,0);
    set_sprite_prop(0x04,0);
    set_sprite_prop(0x05,0);

    set_sprite_prop(0x06,1);
    set_sprite_prop(0x07,1);
    set_sprite_prop(0x08,1);
    set_sprite_prop(0x09,1);
    set_sprite_prop(0x0A,1);
    set_sprite_prop(0x0B,1);
}

void main(void) {
  wait_vbl_done();
  SPRITES_8x8;
  DISPLAY_OFF;

  set_bkg_palette(0x00, 0x01, hudCGB);
  set_bkg_palette(0x01, 0x01, bkgCGB);
  set_sprite_palette(0x00, 0x01, jerdCGB);
  set_sprite_palette(0x01, 0x01, jirardCGB);

  move_win(7,96);
  set_win_data(0x00, 0x2D, hud);
  set_win_tiles(0x00,0x00, 0x14, 0x06, hudEx);

  set_bkg_data(0x2D, 0x02, bkg);
  set_bkg_tiles(0x00,0x00, 0x14, 0x12, bkgEx);

  loadSprites();

  SHOW_BKG;
  SHOW_WIN;
  SHOW_SPRITES;

  DISPLAY_ON;
  while(1) {

  }
}