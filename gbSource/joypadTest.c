#include <stdio.h>
#include <gb/gb.h> //standard library for Game Boy functionality

UINT8 a;

void main(void) {
	printf("Zubie's 1st GB Test!\n--------------------");
    a = 250;
	while(1) {
		switch(joypad()) {
            case J_RIGHT : // if joypad() is equal to RIGHT 
                           // (right button pressed down)
                printf("Right!\n");
                delay(100); //prevents us from misinputting AF
                break;
            case J_LEFT : // see above, for left
                printf("Left!\n");
                delay(100);
                break;
            case J_UP : 
                a++;
                printf("%i\n", a);
                delay(100);
                break;
            case J_DOWN :
                a--;
                printf("%i\n", a);
                delay(100);
                break;
            case J_A :
                if (a < 240)
                    printf("A!\n");
                else
                    printf("The code has been cracked!");
                delay(100);
                break;
            case J_B :
                printf("B!\n");
                delay(100);
                break;
            case J_START :
                printf("Start!\n");
                delay(100);
                break;
            case J_SELECT :
                printf("Select!\n");
                delay(100);
                break;
            default : //the case that nothing is pressed 
                break;
		}
	}
}