#include <gb/gb.h>
#include "C:\Users\abzar\Documents\GBDTools\GameBoyGames\gbSource\Sprites\knight.c"
#include "C:\Users\abzar\Documents\GBDTools\GameBoyGames\gbSource\Sprites\ogre.c"
typedef enum { false, true } bool;

    int pcLeftX = 75;  //beginning coords
    int leftY = 75;
    int pcRightX = 75 + 8; 
    int rightY = 75;
    int enemyOneX = 120;
    int enemyOneY = 75;
    int march = 0; 
    int currentL = 0;
    int currentR = 2;
    bool spriteHasChanged = false;

void loadSprites(void) {
    SPRITES_8x16;
    set_sprite_data(0, 32, knight);
    set_sprite_data(32,40, ogre);
    set_sprite_tile(0, 0);
    move_sprite(0, pcLeftX, leftY);
    set_sprite_tile(1, 2);
    move_sprite(1, pcRightX, rightY);
    set_sprite_tile(2,32);
    move_sprite(2, enemyOneX, enemyOneY);
    set_sprite_tile(3,34);
    move_sprite(3, enemyOneX + 8, enemyOneY);

    SHOW_SPRITES;
}

void spriteChange(int spriteL, int frameL, int spriteR, int frameR) {
    set_sprite_tile(spriteL, frameL);
	set_sprite_tile(spriteR, frameR);
}

bool collisionDetection() {
   return false;
}

void getInput(void) {
    	if (march == 0) {
            spriteChange(0,currentL+4,1,currentR+4);
        }
        else if (march == 15) {
            spriteChange(0,currentL,1,currentR);
        }
    	if (joypad()==J_RIGHT && pcRightX < 161) 
    	{
    		if (currentL != 16) {
    		    currentL = 16;
                currentR = 18;
                spriteHasChanged = true;
            }
            pcLeftX++;
            pcRightX++;
            move_sprite(0,pcLeftX,leftY);
            move_sprite(1,pcRightX,rightY);
    	}
    	if (joypad()==J_LEFT && pcLeftX > 0)
    	{
    		if (currentL != 24) {
    		    currentL = 24;
                currentR = 26;
                spriteHasChanged = true;
            }
            pcLeftX--;
            pcRightX--;
            move_sprite(0,pcLeftX,leftY);
            move_sprite(1,pcRightX,rightY);
    	}
    	if (joypad()==J_UP && leftY > 16 && rightY > 16)
    	{
    		if (currentL != 8) {
    		    currentL = 8;
                currentR = 10;
                spriteHasChanged = true;
            }
    		leftY--;
    		rightY--;
    		move_sprite(0,pcLeftX,leftY);
            move_sprite(1,pcRightX,rightY);
    	}
    	if (joypad()==J_DOWN && leftY < 144 && rightY < 144)
    	{
    		if (currentL != 0) {
    		    currentL = 0;
                currentR = 2;
                spriteHasChanged = true;
            }
    		leftY++;
    		rightY++;
    		move_sprite(0,pcLeftX,leftY);
            move_sprite(1,pcRightX,rightY);
    	}
    	if (march < 30 && !spriteHasChanged)
    		march++;
        else {
        	march = 0;
        	spriteHasChanged = false;
        }
        delay(16);
}

void main(void) {

	loadSprites();

    while (1) {
        getInput();
    }
}