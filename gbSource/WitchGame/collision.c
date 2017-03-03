/*
 * collision detection functions
 */
#include "structs.h"

/*
 * checks collision between player character and various objects
 */
UINT8 collision(spriteData * ptr) {
	UINT8 edges = 0x00;
	if (ptr->y >= 112) {
		ptr->y = 112;
		edges = edges | 0x01;
	}
	else {
		edges = edges & 0xFE;
	}
	return edges;
}

/* performs changes to gravity, respective to collision
 * TODO: fix jumping "feel" and speed
 *       fix modulo glitch (where jumping height is dependent on time)
 */

void gravity(spriteData * ptr, UINT8 t) {
    if ((collision(ptr) & 0x01) && ptr->g <= 0) {
    	ptr->g = 0;
    	ptr->state = ptr->state & 0xFE; // set state bit 1 to grounded
    	return;
    }
    else {
    	if (ptr->g > 0 && t%(4 * ptr->g) == 0) {
            ptr->g--;
    	}
    	if (ptr->g == 0) {
    		ptr->state = ptr->state & 0xFD; // set state bit 2 to falling
    		ptr->g--;
    	}
    	if ((ptr->g > -2 && ptr->g < 0)){
    	    ptr->g--;
    	}
    	ptr->y = ptr->y - ptr->g;
    }
}