#include <gb/gb.h>
#include "bkgTiles/levelOne.c"
#include "bkgTiles/castle.c"
#include "bkgTiles/hud.c"
#include "bkgTiles/hudExample.c"

/*
 * Specific test for getting backgrounds working
 */
void main(void) {

	wait_vbl_done();
	DISPLAY_OFF;
    set_bkg_data(0x00,0x14, castle);
    set_bkg_tiles(0x00, 0x00, 0x14, 0x10, levelOne);

    move_win(7,128);
    set_win_data(0x14,0x05, hud);
    set_win_tiles(0x00,0x00, 0x14, 0x02, hudExample);

    SHOW_BKG;
    SHOW_WIN;

    DISPLAY_ON;
}