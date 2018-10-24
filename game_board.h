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
* @file game_board.h
* Links all the functions of the the game_board.c
*/

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

/**
 * This enum permit to simplify the comprehension of different cases
 */
enum {
    PLAYER = -1,
    BLANK = 1,
    WALL = 0,
    BONUS = -2,
    MALUS = -3
};

/**
 * This enum permit to better visualize the north south east and west
 */
enum{
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

/**
 * This structure permit to have a simple access to the multi dimentional board
 */
typedef struct{
    int **game_board;
    char * name;
    int row;
    int col;
}game_board;

#ifndef PROJET_GAME_BOARD_H
#define PROJET_GAME_BOARD_H

/**
 * This function permit to display the game board with filter
 * @param g_b the structure of the game board
 */
void display_game_board(game_board *g_b);

/**
 * (UNUSED)This function permit to display the game board with filter
 * @param g_b the structure of the game board
 */
void display_game_board_no_filter(game_board *g_b);

/**
 * This function return an odd. If the user enter anything else it recursively call itself
 * @return
 */
int enter_odd();

/**
 * This function initialize the game board with a 0 for a '#', 1 for a " " and 'o' for -1
 * Thanks to this configuration I will not have to handle the last occurence because the last will leave only 1 and 0
 * @param g_b the structure of the game board
 */
void init_game_board(game_board *g_b);

/**
 * This function free the data used from the game board
 * @param g_b the structure of the game board
 */
void free_game_board(game_board *g_b);

/**
 * This function look if the random is correctly set. For exemple if I am at the case of the array where I am at the
 * bottom right corner and the random is set to the right. With this function it will bet set to tbe right
 * @param random_y_x the random number to verify
 * @param pos_x position in the array of x
 * @param pos_y position in the array of y
 * @param g_b structure of the game board
 * @return the final number "randomly" selected
 */
int fill_rand(int random_y_x, int pos_x, int pos_y, game_board * g_b);

/**
 * This function verify if the labyrinthe is finished or not by verifying all the array is set to 1 ot not
 * @param g_b the structure of the game board
 * @return 0 if false 1 if true
 */
int verify_arrays(game_board *g_b);

/**
 * This function is looking into the array all the variable which correspond for changing all the values needing to
 * change
 * @param g_b the structure of the game board
 * @param val the value we are searching in the array
 * @param replace the value with which we are replacing
 */
void change_valeur(game_board *g_b,int val, int replace);

/**
 * This function is looking if the random number exist or not in the array random
 * @param random the array
 * @param seek the value we are searching in the array
 * @return 0 if a value match, 1 otherwise
 */
int verif_random(int random[],int seek);

/**
 * This function permit to set a random number between a and b included
 * @param a the 1st number we are setting the min
 * @param b the 2nd number we are setting the max
 * @return a random number between a and b
 */
int rand_a_b(int a, int b);

/**
 * This function is unused
 * @param height
 * @param random
 */
void false_random(int taille, int random[]);

/**
 * This function destroy the wall between a case of the array and another case on the row position
 * @param random_y_x the number random choosen by random for joining to cases
 * @param g_b the structure of the game board
 * @param pos_y the position of the current case of the array we are looking at on row
 * @param pos_x the position of the current case of the array we are looking at on column
 * @param fact This value depends on if it has to destroy the wall from top or from bottom
 */
void test_destroy_y(int random_y_x,game_board *g_b,int pos_y, int pos_x,int fact);

/**
 * This function destroy the wall between a case of the array and another case on the column position
 * @param random_y_x the number random chosen by random for joining to cases
 * @param g_b the structure of the game board
 * @param pos_y the position of the current case of the array we are looking at on row
 * @param pos_x the position of the current case of the array we are looking at on column
 * @param fact This value depends on if it has to destroy the wall from the right or the left
 */
void test_destroy_x(int random_y_x,game_board *g_b,int pos_y, int pos_x,int fact);

/**
 * This function is destroying all the wall of the labyrinth to generate the perfect labyrinth
 * @param g_b is the structure of the game board
 */
void destroy_walls(game_board *g_b);

/**
 * This function is writing into a file the actual game board
 * @param g_b is the structure of the game board
 */
void print_game_board(game_board *g_b);

/**
 * This function create the labyrinth from nothing
 * @param g_b is the structure of the game board
 */
void create_labyrinthe(game_board *g_b);

/**
 * This function load a labyrinth from a file .cfg
 * @param g_b is the structure of the game board
 */
void load_labyrinthe(game_board *g_b);

/**
 * This function add the treasures and the trap into the game board
 * @param g_b the structure of the game board we want to modify
 */
void add_trap_and_treasure(game_board *g_b);

/**
 * This function initiate the position of the player and the exit of the game board
 * @param g_b the structure of the game board which will be changed
 */
void init_entrance_exit(game_board *g_b);

/**
 * This function initiate the columns and the rows loaded in the game board
 * @param g_b structure game board in which we are working on
 * @param f the file which contains the
 */
void init_col_row_load_gameboard(game_board *g_b, FILE * f);

#endif //PROJET_GAME_BOARD_H
