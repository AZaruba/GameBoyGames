/*
 * h file for all structs used in the game
 */

// data for a sprite's position, as well as it's gamestate
typedef struct {
    UINT8 x;
    UINT8 y;
    INT8 g;
    UINT8 state; // 0th ground/air, 1st fall/rise, 2nd free/hitstun
} spriteData;