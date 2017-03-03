/*
 * h file for all structs used in the game
 */

// data for a sprite's position, as well as it's gamestate
typedef struct {
    UINT8 x;
    UINT8 y;
    INT8 g;
    UINT8 state; /*
                  * each bit corresponds to a different part of sprite state
                  * 0 - grounded	jumping
                  * 1 - rising		falling - NOT NEEDED?
                  * 2 - free		hitstun
                  * 3 - face left	face right
                  * 4 - 7 			unused... for now :)
                  */
} spriteData;