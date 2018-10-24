/**
* ENSICAEN
* 6 Boulevard Maréchal Juin
* F-14050 Caen Cedex
*
* This file is owned by ENSICAEN students. No portion of this
* document may be reproduced, copied or revised without written
* permission of the authors.
*/


/**
* @author Aristide Boisgontier <aboisgontier@ecole.ensicaen.fr>
* @version 0.0.1 - 2018-10-22
*
* @todo nothing else.
* @bug no bugs known.
*/


/**
* @file game_board.c
* All the functions for the creation of the labyrinth
*/

#include "game_board.h"

/**
 * This function permit to display the game board with filter
 * @param g_b the pointer array multidimentional
 */
void display_game_board(game_board *g_b) {
    for (int i = 0; i < g_b->row; ++i) {
        for (int j = 0; j < g_b->col; ++j) {
            if (g_b->game_board[i][j] == WALL) {
                printf("#");
            } else if (g_b->game_board[i][j] == BLANK) {
                printf(" ");
            } else if(g_b->game_board[i][j] == PLAYER) {
                printf("%c",111);
            } else if(g_b->game_board[i][j] == BONUS) {
                printf("+");
            } else if(g_b->game_board[i][j] == MALUS) {
                printf("X");
            } else {
                printf("%d",g_b->game_board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * (UNUSED)This function permit to display the game board with filter
 * @param g_b the pointer array multidimentional
 */
void display_game_board_no_filter(game_board *g_b) {
    for (int i = 0; i < g_b->row; ++i) {
        for (int j = 0; j < g_b->col; ++j) {
            printf("%d",g_b->game_board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * This function return an odd. If the user enter anything else it recursively call itself
 * @return
 */
int enter_odd() {
    int number;
    scanf("%d",&number);
    if (number%2 == 0 || number <= 0) {
        number++;
        printf("Wrong enter, isn't odd so I filled +1 to your number : %d\n",number);
    }
    return number;

}

/**
 * This function initiate the position of the player and the exit of the game board
 * @param g_b the structure of the game board which will be changed
 */
void init_entrance_exit(game_board *g_b) {
    int entrance = 1;
    int exit = g_b->row-2;
    g_b->game_board[entrance][0] = PLAYER;
    g_b->game_board[exit][g_b->col-1] = BLANK;
}

/**
 * This function initialize the game board with a 0 for a '#', 1 for a " " and 'o' for -1
 * Thanks to this configuration I will not have to handle the last occurence because the last will leave only 1 and 0
 * @param g_b the structure of the game board
 */
void init_game_board(game_board *g_b) {
    int count = 0;
    init_entrance_exit(g_b);
    for (int i = 1; i < g_b->row - 1; i += 2) {
        for (int j = 1; j < g_b->col - 1; j  += 2) {
            g_b->game_board[i][j] = ++count ;
        }
    }
}

/**
 * This function free the data used from the game board
 * @param g_b the structure of the game board
 */
void free_game_board(game_board *g_b) {
    for (int j = 1; j < g_b->row; ++j) {
        free(g_b->game_board[j]);
    }
    free(g_b->game_board);
    free(g_b->name);
}

/**
 * This function look if the random is correctly set. For exemple if I am at the case of the array where I am at the
 * bottom right corner and the random is set to the right. With this function it will bet set to tbe right
 * @param random_y_x the random number to verify
 * @param pos_x position in the array of x
 * @param pos_y position in the array of y
 * @return the final number "randomly" selected
 */
int fill_rand(int random_y_x, int pos_x, int pos_y, game_board * g_b) {
    int last_empty_case_y = g_b->row - 2;
    int last_empty_case_x = g_b->col - 2;
    if(pos_x == last_empty_case_y) {
        if (random_y_x == SOUTH) {
            random_y_x -= 2;
        } else if (pos_y == 1 && random_y_x == WEST) {
            random_y_x -= 2;
        } else if (pos_y == last_empty_case_x && random_y_x == EAST) {
            random_y_x += 2;
        }
    } else if (pos_x == 1) {
        if (random_y_x == NORTH) {
            random_y_x += 2;
        } else if (pos_y == 1 && random_y_x == WEST) {
            random_y_x -=2;
        } else if (pos_y == last_empty_case_x && random_y_x == EAST) {
            random_y_x += 2;
        }
    } else if (pos_y == 1 && random_y_x == WEST) {
        random_y_x -= 2;
    } else if (pos_y == last_empty_case_x && random_y_x == EAST) {
        random_y_x += 2;
    }
    return random_y_x;
}

/**
 * This function verify if the labyrinthe is finished or not by verifying all the array is set to 1 ot not
 * @param g_b the structure of the game board
 * @return 0 if false 1 if true
 */
int verify_arrays(game_board *g_b) {
    for (int i = 1; i <= g_b->row - 1; i+= 2) {
        for (int j = 1; j <= g_b->col - 1; j += 2) {
            if (g_b->game_board[i][j] != 1) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * This function is looking into the array all the variable which correspond for changing all the values needing to
 * change
 * @param g_b the structure of the game board
 * @param val the value we are searching in the array
 * @param replace the value with which we are replacing
 */
void change_valeur(game_board *g_b,int val, int replace) {
    for (int i = 1; i < g_b->row - 1; i++) {
        for (int j = 1; j < g_b->col - 1; j ++) {
            if (g_b->game_board[i][j] == val) {
                g_b->game_board[i][j] = replace;
            }
        }
    }
}

/**
 * This function is looking if the random number exist or not in the array random
 * @param random the array
 * @param seek the value we are searching in the array
 * @return 0 if a value match, 1 otherwise
 */
int verif_random(int random[],int seek) {
    for (int i = 0; i < sizeof(random); ++i) {
        if (random[i] == seek) {
            return 0;
        }
    }
    return 1;
}

/**
 * This function permit to set a random number between a and b included
 * @param a the 1st number we are setting the min
 * @param b the 2nd number we are setting the max
 * @return a random number between a and b
 */
int rand_a_b(int a, int b) {
    return rand()%(b-a)+a;
}

/**
 * This function is unused
 * @param height the the array to test
 * @param random the number random to test
 */
void false_random(int height, int random[]) {
    int n = height*2-3;
    int temp;
    for (int i = 0; i < n; ++i) {
        int flag = 0;
        while (flag != 1) {
            temp = rand_a_b(1,44);
            if (verif_random(random,temp) == 1) {
                flag = 1;
                random[i] = temp;
            }
        }
    }
}

/**
 * This function destroy the wall between a case of the array and another case on the row position
 * @param random_y_x the number random choosen by random for joining to cases
 * @param g_b the structure of the game board
 * @param pos_y the position of the current case of the array we are looking at on row
 * @param pos_x the position of the current case of the array we are looking at on column
 * @param fact This value depends on if it has to destroy the wall from top or from bottom
 */
void test_destroy_y(int random_y_x,game_board *g_b,int pos_y, int pos_x,int fact) {
    int temp;
    if (g_b->game_board[pos_y][pos_x] != g_b->game_board[fact][pos_x]) {
        if (g_b->game_board[pos_y][pos_x] < g_b->game_board[fact][pos_x]) {
            temp = g_b->game_board[pos_y][pos_x];
            change_valeur(g_b,g_b->game_board[fact][pos_x],g_b->game_board[pos_y][pos_x]);
        } else {
            temp = g_b->game_board[fact][pos_x];
            change_valeur(g_b,g_b->game_board[pos_y][pos_x],g_b->game_board[fact][pos_x]);
        }
        if (random_y_x == 1) {
            g_b->game_board[pos_y-1][pos_x] = temp;
        } else {
            g_b->game_board[pos_y+1][pos_x] = temp;
        }
    }
}

/**
 * This function destroy the wall between a case of the array and another case on the column position
 * @param random_y_x the number random chosen by random for joining to cases
 * @param g_b the structure of the game board
 * @param pos_y the position of the current case of the array we are looking at on row
 * @param pos_x the position of the current case of the array we are looking at on column
 * @param fact This value depends on if it has to destroy the wall from the right or the left
 */
void test_destroy_x(int random_y_x,game_board *g_b,int pos_y, int pos_x, int fact) {
    int temp;
    if (g_b->game_board[pos_y][pos_x] != g_b->game_board[pos_y][fact]) {
        if (g_b->game_board[pos_y][pos_x] < g_b->game_board[pos_y][fact]) {
            temp = g_b->game_board[pos_y][pos_x];
            change_valeur(g_b,g_b->game_board[pos_y][fact],g_b->game_board[pos_y][pos_x]);
        } else {
            temp = g_b->game_board[pos_y][fact];
            change_valeur(g_b,g_b->game_board[pos_y][pos_x],g_b->game_board[pos_y][fact]);
        }
        if (random_y_x == 4) {
            g_b->game_board[pos_y][pos_x-1] = temp;
        } else {
            g_b->game_board[pos_y][pos_x+1] = temp;
        }
    }
}

/**
 * This function is destroying all the wall of the labyrinth to generate the perfect labyrinth
 * @param g_b the structure of the game board
 */
void destroy_walls(game_board *g_b) {
    int random;
    int empty_cases = ((g_b->row-1)*(g_b->col-1))/4;
    int random_y_x;
    int flag = 0;
    int count;
    int i;
    while(flag == 0) {
        random = rand_a_b(1,empty_cases);
        count = 0;
        for (i = 1; i < g_b->row-1; i+= 2) {
            for (int j = 1; j < g_b->col-1; j+= 2) {
                count++;
                if (random == count) {
                    random_y_x = rand_a_b(1,4);
                    random_y_x = fill_rand(random_y_x,i,j,g_b);
                    if (random_y_x == 1) {
                        test_destroy_y(random_y_x,g_b,i,j,i-2);
                    } else if (random_y_x == 2) {
                        test_destroy_x(random_y_x,g_b,i,j,j+2);
                    } else if(random_y_x == 3) {
                        test_destroy_y(random_y_x,g_b,i,j,i+2);
                    } else if (random_y_x == 4) {
                        test_destroy_x(random_y_x,g_b,i,j,j-2);
                    }
                }
            }
        }
        flag = verify_arrays(g_b);
    }
}

/**
 * This function is writing into a file the actual game board
 * @param g_b the structure of the game board
 */
void print_file_game_board(game_board *g_b) {
    char * name_file = NULL;
    name_file = malloc(strlen(g_b->name)+5);
    name_file[0] = '\0';
    strcat(name_file,g_b->name);
    strcat(name_file,".cfg");
    FILE * file = fopen(name_file,"w");
    int count = 0;
    if (file != NULL) {
        for (int i = 0; i < g_b->row; ++i) {
            for (int j = 0; j < g_b->col; ++j) {
                if (g_b->game_board[i][j] == WALL) {
                    fputc('#',file);
                } else if (g_b->game_board[i][j] == BLANK) {
                    fputc(' ',file);
                } else if(g_b->game_board[i][j] == PLAYER) {
                    fputc('o',file);
                } else if(g_b->game_board[i][j] == BONUS) {
                    fputc('+',file);
                } else if(g_b->game_board[i][j] == MALUS) {
                    fputc('X',file);
                }
                count++;
            }
            fputc('\n',file);
        }
        fclose(file);
    }
    free(name_file);
}

/**
 * This function add the treasures and the trap into the game board
 * @param g_b the structure of the game board we want to modify
 */
void add_trap_and_treasure(game_board *g_b) {
    int number_trap_and_treasure = (g_b->row*g_b->col)/30;
    if (number_trap_and_treasure != 0) {
        int random_case_row;
        int random_case_col;
        int flag;
        for (int i = 1; i <= number_trap_and_treasure; ++i) {
            flag = 0;
            while (flag == 0) {
                random_case_row = rand_a_b(1, g_b->row - 1);
                random_case_col = rand_a_b(1, g_b->col - 1);
                if (g_b->game_board[random_case_row][random_case_col] == BLANK) {
                    if (i%2 == 0) {
                        g_b->game_board[random_case_row][random_case_col] = BONUS;
                    } else {
                        g_b->game_board[random_case_row][random_case_col] = MALUS;
                    }
                    flag = 1;
                }
            }
        }
    }
}

/**
 * This function create the labyrinth from nothing
 * @param game_board
 */
void create_labyrinthe(game_board *g_b) {
    int y;
    int x;
    printf("Make a labyrinth.\n");
    printf("Please enter an odd number which will be the height of your labyrinth : ");
    y = enter_odd();
    printf("Please enter an odd number which will be the width of your labyrinth :");
    x = enter_odd();

    g_b->col = x;
    g_b->row = y;

    g_b->game_board = calloc(g_b->row,sizeof(int*));
    for (int i = 0; i < y; ++i) {
        g_b->game_board[i] = calloc(g_b->col,sizeof(int));
    }
    init_game_board(g_b);
    display_game_board(g_b);

    destroy_walls(g_b);
    add_trap_and_treasure(g_b);

    display_game_board(g_b);
    printf("Your labyrinth has been created\nPlease enter a name to your labyrinth : ");
    scanf("%s",g_b->name);
    print_file_game_board(g_b);
}

/**
 * This function initiate the columns and the rows loaded in the game board
 * @param g_b structure game board in which we are working on
 * @param f the file which contains the file on which we are working on
 */
void init_col_row_load_gameboard(game_board *g_b, FILE * f) {
    int c;
    while ((c = fgetc(f))!= EOF) {
        if (c == '\n') {
            g_b->row++;
        } else if(g_b->row == 0) {
            g_b->col++;
        }
    }
    fseek(f,0,0);

    g_b->game_board = calloc(g_b->row,sizeof(int*));
    for (int i = 0; i < g_b->col; ++i) {
        g_b->game_board[i] = calloc(g_b->col,sizeof(int));
    }
    int i = 0;
    int j = 0;
    while ((c = fgetc(f))!= EOF) {
        if (c == '#') {
            g_b->game_board[i][j] = WALL;
            j++;
        } else if (c == ' ') {
            g_b->game_board[i][j] = BLANK;
            j++;
        } else if(c == 'o') {
            g_b->game_board[i][j] = PLAYER;
            j++;
        } else if(c == '+') {
            g_b->game_board[i][j] = BONUS;
            j++;
        } else if(c == 'X') {
            g_b->game_board[i][j] = MALUS;
            j++;
        } else if(c == '\n') {
            i++;
            j = 0;
        }
    }
}

/**
 * This function load a labyrinth from a file .cfg
 * @param g_b the structure of the game board
 */
void load_labyrinthe(game_board *g_b) {
    FILE * file;
    char * line = malloc(sizeof(char*));
    char * name_file = NULL;
    name_file = malloc(strlen(g_b->name)+5);
    name_file[0] = '\0';
    strcat(name_file,g_b->name);
    strcat(name_file,".cfg");
    file = fopen(name_file,"r");
    g_b->row = 0;
    g_b->col = 0;
    if (file != NULL) {
        init_col_row_load_gameboard(g_b,file);
        printf("Game loaded\n");
        fclose(file);
    } else {
        printf("The file %s selected doesn't exit", g_b->name);
    }
    free(line);
    free(name_file);
}


