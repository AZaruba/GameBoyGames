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

typedef struct {
  UINT8 t;  // global timer
  UINT8 st; // sprite frame timer
  UINT8 gr; // gravity timer
  UINT8 h;  // which buttons are being held down?
  UINT8 vr; // how far along are we in vram?
  UINT8 collider; // store tiles for collision detection here

} gameData;