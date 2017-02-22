#include <gb/gb.h>
#include "bkgTiles/levelOne.c"
#include "bkgTiles/castle.c"

/*
 * Specific test for getting backgrounds working
 */
void main(void) {

	wait_vbl_done();
	DISPLAY_OFF;
    set_bkg_data(0x00,0x13, castle);
    VBK_REG = 1;
    VBK_REG = 0;
    set_bkg_tiles(0x00, 0x00, 0x12, 0x12, levelOne);

    SHOW_BKG;

    DISPLAY_ON;
}