/* 
 * File:   functions.h
 * Author: Missionpage
 *
 */
 
    #ifndef FUNCTIONS_H
    #define FUNCTIONS_H
    
    #include <stdio.h>
    #include <time.h>
    #include <math.h>
    
    #define MAX_NAME 30
    
/*
 Structs
 */

typedef struct _game{
    int max;
    int score;
    int plus;
    int win;
    int grid[4][4];
    int bgrid[4][4];
}Game;

typedef struct _gameLog{
    char control;
    int stuck;
    int response;
    int exitGame;
    int lose;
}GameLog;

typedef struct _gameInterf{
    char option;
    char name[MAX_NAME];
}GameInterf;
    
/*
 Functions prototypes
 */

void logic_flow(Game* Game, GameLog* GameLog);

int random_index(int x);
int partSize(int n);
void start_grid(Game* Game);
void backup_grid(Game* Game);
void key_pressed(GameLog* GameLog);
void display_grid(Game* Game);
void spawn(Game* Game);
void fill_space(Game* Game, GameLog* GameLog);
void find_great_tile(Game* Game);
int full(Game* Game);
int block_moves(Game* Game);
void undo(Game* Game);
void update_grid(Game* Game, GameLog* GameLog);


void game_end_check(Game* Game, GameLog* GameLog, GameInterf* GameInterf);

void display_help_screen();
void display_win_screen(Game* Game, GameInterf* GameInterf);
void display_loser_screen(Game* Game, GameInterf* GameInterf);
char try_again_screen(int lose, GameInterf* GameInterf);

/*
 Functions definition
 */

int random_index(int x){
    
    int index;
    
    index = rand()%x + 0;
    
    return index;
}

/*
 I added this function because of problems with math.h
 Seems that it do not want to recognise log2.
*/

int partSize(int n){
    return log2(n);
}

void start_grid(Game* Game){
    
    int i, j;
    
    Game->plus = 0;
    Game->score = 0;
    Game->max = 0;
    Game->win = 2048;
    
    /*
    We asign '0' to every square of the matrix
    */
    
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){ 
            Game->grid[i][j] = 0;
        }
    }
    
    /*
    One '2' is putted on the matrix
    */
    
    i = random_index(4);
    j = random_index(4);
    
    Game->grid[i][j] = 2;
    
    /*
    Another '2' is putted on the matrix
    */
    
    i = random_index(4);
    j = random_index(4);
    
    Game->grid[i][j] = 2;
}

void backup_grid(Game* Game){
    
    int i, j;
    
    /*
    We copy the actual matrix (grid[i][j])
    */
    
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            Game->bgrid[i][j] = Game->grid[i][j];
        }
    }
}

void key_pressed(GameLog* GameLog){
    
    char ctrl;
    
    scanf("%c", &ctrl);
    
    GameLog->control = ctrl;
}

void display_grid(Game* Game){
    
    int i, j;
    
    /*
     In case of Windows, which is my main OS, I've putted system("clear"); but, in case you're using Linux, you have to change the line below for this one: system("clear");
     */
    
    system("clear");
    
    /*
     Prints the name of the game and the name of the dev
     */
    
    fprintf(stdout, "\n       The 2048 GAME     \t\t\t\tDeveloped by Luis Egui\n\n\t");
    
    /*
     Prints the new score (that's was added) to the previous score
     */
    
    if(Game->plus){
        fprintf(stdout, "+ %d!", Game->plus);
    }else
        fprintf(stdout, "   ");
    
    /*
     Prints the actual score
     */
    
    fprintf(stdout, "\t\t\t\t\t\tSCORE: %d \n\n\n\n", Game->score);
    
    for(i = 0; i < 4; i++){
        
        fprintf(stdout, "\t\t     |");
        
        for(j = 0; j < 4; j++){
            
            /*
             In case there's any number in the matrix, it will print those numbers, otherwise, it'll print a space (it is the alternative of putting a 0)
             */
            
            if(Game->grid[i][j]){
                printf("%4d    |", Game->grid[i][j]);
            }else
                printf("%4c    |", ' ');
        }
        
        fprintf(stdout, "\n\n");
    }
    
    fprintf(stdout, "\n\n Controls \t\t\t\tu - undo\tr - restart\n\n\tW\t\t     \t\th - help\tq - quit\n\t\t\t\t\t\t\t\t");
    fprintf(stdout, " \n   A    S    D");
    fprintf(stdout, " \n\t\t\t\t                             ");
}

void spawn(Game* Game){
    
    int i, j, k;
    
    /*
     This will generate less 4s than 2s (20%-80%)
     */
    
    do{
        i = random_index(4);
        j = random_index(4);
        k = random_index(10);
        
    }while(Game->grid[i][j]);
    
    if(k < 2){
        Game->grid[i][j] = 4;
    }else{
        Game->grid[i][j] = 2;
    }
}

/*
    Moves the numbers of the grid to the direction that the user says
    
*/

void fill_space(Game* Game, GameLog* GameLog){
    
    int row, col, col2, row2;
    
    switch(GameLog->control){
        
        case 'w': 
            
            for(col = 0; col < 4; col++)
            {
                for(row = 0; row < 4; row++)
                {
                    if(!Game->grid[row][col])
                    {
                        for(row2 = row+1; row2 < 4; row2++)
                        {
                            if(Game->grid[row2][col])
                            {
                                Game->grid[row][col] = Game->grid[row2][col];
                                Game->grid[row2][col] = 0;
                                
                                break;
                            }
                        }
                    }
                }
            }
            
            break;
                
        case 's': 
            
            for(col = 0; col < 4; col++)
            {
                for(row = 3; row >= 0; row--)
                {
                    if(!Game->grid[row][col])
                    {
                        for(row2 = row-1; row2 >= 0; row2--)
                        {
                            if(Game->grid[row2][col])
                            {
                                Game->grid[row][col] = Game->grid[row2][col];
                                Game->grid[row2][col] = 0;
                                
                                break;
                            }
                        }
                    }
                }
            }
            
            break;
            
        case 'a':

            for (row = 0; row < 4; row++)
            {
                for (col = 0; col < 4; col++)
                {
                    if (!Game->grid[row][col])
                    {
                        for (col2 = col+1; col2 < 4; col2++)
                        {
                            if (Game->grid[row][col2])
                            {
                                Game->grid[row][col] = Game->grid[row][col2];
                                Game->grid[row][col2] = 0;
                                
                                break;
                            }
                        }
                    }
                }
            }
            
            break;
            
        case 'd':
            
            for(row = 0; row < 4; row++)
            {
                for(col = 3; col >= 0; col--)
                {
                    if(!Game->grid[row][col])
                    {
                        for(col2 = col-1; col2 >= 0; col2--)
                        {
                            if(Game->grid[row][col2])
                            {
                                Game->grid[row][col] = Game->grid[row][col2];
                                Game->grid[row][col2] = 0;
                                
                                break;
                            }
                        }
                    }
                }
            }
            
            break;
       }
}

/*
    This function search the max tile that you have in your grid.
    Just to check if you have done 2048.
*/

void find_great_tile(Game* Game){
    
    int i, j;
    
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(Game->grid[i][j] > Game->max){
                Game->max = Game->grid[i][j];
            }
        }
    }
    
}

/*
    Checks if the grid is full
*/

int full(Game* Game){
    
    int i, j;
    int k = 1;
    
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(!Game->grid[i][j]){
                k = 0;
            }
        }
    }
    
    return k;
}

/*
    Checks if you have moved the grid
*/

int block_moves(Game* Game){
    
    int i, j;
    int k = 0;
    
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(Game->bgrid[i][j] != Game->grid[i][j]){
                k = 1;
                break;
            }
        }
    }
    
    return k;
}

/*
    Goes back to your last move
*/

void undo(Game* Game){
    
    int i, j;
    
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            Game->grid[i][j] = Game->bgrid[i][j];
        }
    }
}

/*
    This is the merge function.
*/

void update_grid(Game* Game, GameLog* GameLog){
    
    int row, col, row2, col2;
    int aux, aux2;
    
    Game->plus = 0;
    GameLog->stuck = 1;
    
    switch(GameLog->control){
        
        case 'w':
            
           for(col = 0; col < 4; col++)
            {
                for(row = 0; row < 4; row++)
                {
                    if(Game->grid[row][col])
                    {
                        row2 = row+1;
                        
                        if(Game->grid[row2][col])
                        {
                            if(Game->grid[row][col] == Game->grid[row2][col])
                            {
                                Game->grid[row][col] *= 2;
                                
                                /*
                                 (log2(value of the box [col][row]) - 1) * value of the box [col][row])
                                */
                                
                                aux2 = Game->grid[col][row];
                                aux = partSize(aux2);
                                
                                Game->plus +=  ( (aux  - 1) * aux2 );
                                Game->score += Game->plus;
                                
                                GameLog->stuck = 0;
                                Game->grid[row2][col] = 0;
                            }
                        }
                    }
                }
            }
            
            break;
            
        case 's':
            
            for(col = 0; col < 4; col++)
            {
                for(row = 3; row >= 0; row--)
                {
                    if(Game->grid[row][col])
                    {
                        row2 = row-1;
                        
                        if(Game->grid[row2][col])
                        {
                            if(Game->grid[row][col] == Game->grid[row2][col])
                            {
                                Game->grid[row][col] *= 2;
                                
                                /*
                                 (log2(value of the box [col][row]) - 1) * value of the box [col][row])
                                */
                                
                                aux2 = Game->grid[col][row];
                                aux = partSize(aux2);
                                
                                Game->plus +=  ( (aux  - 1) * aux2 );
                                Game->score += Game->plus;
                                
                                GameLog->stuck = 0;
                                Game->grid[row2][col] = 0;
                            }
                        }
                    }
                }
            }
            
            break;
            
        case'a':
            
            for(row = 0; row < 4; row++)
            {
                for(col = 0; col < 4; col++)
                {
                    if(Game->grid[row][col])
                    {
                        col2 = col+1;
                            
                        if(Game->grid[row][col2])
                        {
                            if(Game->grid[row][col] == Game->grid[row][col2])
                            {
                                Game->grid[row][col++] *= 2;
                                
                                /*
                                 (log2(value of the box [col][row]) - 1) * value of the box [col][row])
                                */
                                
                                aux2 = Game->grid[col][row];
                                aux = partSize(aux2);
                                
                                Game->plus +=  ( (aux  - 1) * aux2 );
                                Game->score += Game->plus;
                                
                                GameLog->stuck = 0;
                                Game->grid[row][col2] = 0;
                            }
                        }
                    }
                }
            }
            
            break;
            
        case 'd':
            
            for(row = 0; row < 4; row++)
            {
                for(col = 3; col >= 0; col--)
                {
                    if(Game->grid[row][col])
                    {
                        col2 = col-1;
                        
                        if(Game->grid[row][col2])
                        {
                            if(Game->grid[row][col] == Game->grid[row][col2])
                            {
                                Game->grid[row][col] *= 2;
                                
                                /*
                                 (log2(value of the box [col][row]) - 1) * value of the box [col][row])
                                */
                                
                                aux2 = Game->grid[col][row];
                                aux = partSize(aux2);
                                
                                Game->plus +=  ( (aux  - 1) * aux2 );
                                Game->score += Game->plus;
                                
                                GameLog->stuck = 0;
                                Game->grid[row][col2] = 0;
                            }
                        }
                    }
                }
            }
            
            break;
    }
}

/*
    This is how the game works. See main.c
*/

void logic_flow(Game* game, GameLog* gameLog){
    
    switch(gameLog->control){
        
        case 'w':
        case 's':
        case 'a':
        case 'd':
        
            backup_grid(game);
            
            fill_space(game, gameLog);
            update_grid(game, gameLog);
            fill_space(game, gameLog);
            
            find_great_tile(game);
            display_grid(game);
            
            gameLog->exitGame = 0;
            gameLog->lose = 0;
            
            if(full(game) && gameLog->stuck){
                gameLog->response = -1;
                gameLog->lose = 1;
                break;
            }else if(block_moves(game)){
                spawn(game);
                break;
            }else{
                gameLog->response = 0;
                break;
            }
            
        case 'u':
        
            if(block_moves(game)){
                game->score -= game->plus;
                undo(game);
                break;
            }
            
        case 'r':
            
            start_grid(game);
            game->plus = 0;
            game->score = 0;
            
            break;
            
        case 'q':
            
            gameLog->response = -1;
            gameLog->exitGame = 1;
            break;
           
        case 'h':
        
            display_help_screen();
            
            break;
            
    }
    
}

void display_help_screen(){
    
    system("clear");
    
    getchar();

    fprintf(stdout, "\n       The 2048 GAME     \t\t\t\tDeveloped by Luis Egui\n\n\t");
    
    fprintf(stdout, "--> The game starts with 1 or 2 randomly placed numbers in a 4x4 grid (16 cells).\n\t");
    fprintf(stdout, "--> Use the controls to move the cells. ( Press W/A/S/D )\n\t");
    fprintf(stdout, "--> 2 cells of the same number will merge and add up\n\t");
    fprintf(stdout, "--> New 2s and 4s will appear randomly on an empty cell with each move you make.\n\t");
    fprintf(stdout, "--> Your objective is to make 2048 in a cell without getting stuck\n\n\t");
    fprintf(stdout, " Press Enter to continue...\n\t");
    
    getchar();
    
}


void display_win_screen(Game* Game, GameInterf* GameInterf){
    
    system("clear");
    
    fprintf(stdout, "\n\n");
    fprintf(stdout, "\n\t\t\t     [  YOU MADE %d !  ]\n\n\t\t\t     [  YOU WON THE GAME!  ]\n\n\n\n\t\t\t TILE\t     SCORE\t    NAME", Game->win);
    printf("\n\n\t\t\t %4d\t    %6d\t    ", Game->max, Game->score);
    scanf("%s", GameInterf->name);
    fprintf(stdout, "\n\n\t\t> The maximum possible tile is 65,536 !");
}

void display_loser_screen(Game* Game, GameInterf* GameInterf){
    
    system("clear");
    
    fprintf(stdout, "\n\n\n\t\t\t     [ G A M E  O V E R ]   \n\n\n\n\t\t\t TILE\t     SCORE\t    NAME");
    printf("\n\n\t\t\t %4d\t\t%4d    %6s\t    ", Game->max,Game->score, GameInterf->name);
    scanf("%s", GameInterf->name);
    fprintf(stdout, "\n\n\t\t> The maximum possible score is 3,932,156 !");
}

char try_again_screen(int lose, GameInterf* GameInterf){
    
    if(lose){
        fprintf(stdout, "\n\n\n\t    > Would you like to try again %s (y/n) ?", GameInterf->name);
    }else
        fprintf(stdout, "\n\n\n\t    > Would you like to continue playing %s (y/n) ?", GameInterf->name);
    
    scanf("%c", &GameInterf->option);
    
    return GameInterf->option;
}

void game_end_check(Game* Game, GameLog* GameLog, GameInterf* GameInterf){

    if(Game->max == Game->win){
        display_win_screen(Game, GameInterf);
        
        if(try_again_screen(0, GameInterf) == 'n'){
            GameLog->response =  -1;
            exit(EXIT_SUCCESS);
        }else
            Game->win *= 2;
        
    }else if(GameLog->response == -1 && GameLog->lose == 1){
        display_loser_screen(Game, GameInterf);
        
        if(try_again_screen(1, GameInterf) == 'y'){
            start_grid(Game);
            GameLog->response = 0;
        }else if(try_again_screen(1, GameInterf) == 'n'){
            exit(EXIT_SUCCESS);
        }
    }
    
    if(GameLog->response == -1 && GameLog->exitGame == 1){
        fprintf(stdout, "\n\n\t\t            > Thank you for playing. \n\n\n\t\t\t\t\t\t   Developed by Luis Egui.\n\n");
        exit(EXIT_SUCCESS);
    }
        
}

#endif