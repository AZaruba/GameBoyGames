/*
 * collision detection functions
 */
//#include "structs.h"

/*
 * checks collision between player character and various objects
 */
UINT8 collision(spriteData * ptr, gameData * stats) {
	UINT8 edges = 0x00;
    //UINT8 bkgColH = ptr->x; // horiz tile occupied by sprite
    //UINT8 bkgColV = ptr->y + 24; // vert tile occupied by sprite
    //bkgColH = bkgColH >> 3;
    //bkgColV = bkgColV >> 3;

    if (ptr->y >= 112) {
        ptr->y = 112;
        edges = edges | 0x01;
    }
    // here goes calculations on loaded background tiles
    //bkgColV++;
    //get_bkg_tiles(bkgColH, bkgColV, 0x01, 0x01, &stats->colliderL);
    //get_bkg_tiles(bkgColH + 1, bkgColV, 0x01, 0x01, &stats->colliderR);

    //if (stats->colliderL == 0x0F || stats->colliderL == 0x0D){
    //    ptr->y = 32;
    //    ptr->g = 2;
    //    edges = edges | 0x01;
    //} else if (stats->colliderR == 0x0F || stats->colliderR == 0x0D) {
    //    ptr->y = 32;
    //    edges = edges | 0x01;
    //}
    
	//else {
	//	edges = edges & 0xFE;
	//}
	return edges;
}

/* performs changes to gravity, respective to collision
 * TODO: fix jumping "feel" and speed
 *       fix modulo glitch (where jumping height is dependent on time)
 */
void gravity(spriteData * ptr, gameData * stats) {
	// checks if there is ground below the character
    if ((collision(ptr, stats->collider) & 0x01) && ptr->g <= 0) {
    	//ptr->g = 0;
    	//ptr->state = ptr->state & 0xFE; // set state bit 1 to grounded
        stats->gr = 0; // reset gravity timer
    	return;
    }

    // gravity function, on what frames do we update position
    else {
    	if (ptr->g > 0 && stats->gr%6 == 0) {
            ptr->g--;
    	}
    	if (ptr->g == 0 && stats->gr%6 == 0) {
    		ptr->state = ptr->state & 0xFD; // set state bit 2 to falling
    		ptr->g--;
    	}
    	if ((ptr->g > -3 && ptr->g < 0 && stats->gr%6 == 0)){
    	    ptr->g--;
    	}
    	ptr->y = ptr->y - ptr->g;
        stats->t++;
        stats->gr++;
    }
}