#include <gb/gb.h>
#include "Sprites/floor.c"
#include "Sprites/heart.c"

/*
 * Specific test for getting backgrounds working
 */
void main(void) {

	DISPLAY_OFF;
    wait_vbl_done();
    set_bkg_data(0, 1, floor);
    set_bkg_tiles(0, 0, 0, 0, floor);
    SHOW_BKG;

    DISPLAY_ON;
}