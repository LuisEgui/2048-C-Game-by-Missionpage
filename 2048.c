/* 
 * File:   2048.c
 * Author: Missionpage
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "functions.h"

/*
#include <windows.h>
*/

int main(){
    
    Game game;
    GameLog gameLog;
    GameInterf gameInterf;
        
    srand(time(NULL));
    
    start_grid(&game);
    
    while(1){
    
        display_grid(&game);
    
        key_pressed(&gameLog);
    
        logic_flow(&game, &gameLog);
        
        game_end_check(&game, &gameLog, &gameInterf);
    }
    
    return 0;
}