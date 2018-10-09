//
// Created by arist on 08/10/2018.
//

#ifndef PROJET_GAME_BOARD_H
#define PROJET_GAME_BOARD_H
/**
 * This function permit to display the game board with filter
 * @param game_board the pointer array multidimentional
 * @param row the number of rows
 * @param column the number of columns
 */
void display_game_board(int **game_board, int row, int column);

/**
 * This function permit to display the game board with filter
 * @param game_board the pointer array multidimentional
 * @param row the number of rows
 * @param column the number of columns
 */
void display_game_board_no_filter(int **game_board, int row, int column);

/**
 * This function return an odd. If the user enter anything else it recursively call itself
 * @return
 */
int enter_odd();

/**
 * This function initialize the game board with a 0 for a '#', 1 for a " " and 'o' for -1
 * Thanks to this configuration I will not have to handle the last occurence because the last will leave only 1 and 0
 * @param game_board the pointer array multidimentional
 * @param row the number of rows
 * @param column the number of columns
 */
void init_game_board(int **game_board,int row, int column);

/**
 * This function free the data used from the game board
 * @param game_board the pointer array multidimentional
 */
void destroy_game_board(int **game_board);

/**
 * This function look if the random is correctly set. For exemple if I am at the case of the array where I am at the
 * bottom right corner and the random is set to the right. With this function it will bet set to tbe right
 * @param random_y_x the random number to verify
 * @param pos_x position in the array of x
 * @param pos_y position in the array of y
 * @param row number of row
 * @param column number of columns
 * @return the final number "randomly" selected
 */
int fill_rand(int random_y_x, int pos_x, int pos_y,int row, int column);

/**
 * This function verify if the labyrinthe is finished or not by verifying all the array is set to 1 ot not
 * @param game_board
 * @param row
 * @param column
 * @return 0 if false 1 if true
 */
int verify_arrays(int **game_board,int row, int column);

/**
 * This function is looking into the array all the variable which correspond for changing all the values needing to
 * change
 * @param gameboard
 * @param val the value we are searching in the array
 * @param replace the value with which we are replacing
 * @param row
 * @param column
 */
void change_valeur(int **gameboard,int val, int replace, int row, int column);

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
 * Function still on work
 * @param taille
 * @param random
 */
void false_random(int taille, int random[]);

/**
 * This function destroy the wall between a case of the array and another case on the row position
 * @param random_y_x the number random choosen by random for joining to cases
 * @param gameboard
 * @param pos_y the position of the current case of the array we are looking at on row
 * @param pos_x the position of the current case of the array we are looking at on column
 * @param fact This value depends on if it has to destroy the wall from top or from bottom
 * @param row
 * @param column
 */
void test_destroy_y(int random_y_x,int ** gameboard,int pos_y, int pos_x,int fact, int row, int column);

/**
 * This function destroy the wall between a case of the array and another case on the column position
 * @param random_y_x the number random choosen by random for joining to cases
 * @param gameboard
 * @param pos_y the position of the current case of the array we are looking at on row
 * @param pos_x the position of the current case of the array we are looking at on column
 * @param fact This value depends on if it has to destroy the wall from the right or the left
 * @param row
 * @param column
 */
void test_destroy_x(int random_y_x,int ** gameboard,int pos_y, int pos_x,int fact, int row, int column);

/**
 * This function is destroying all the wall of the labyrinthe to generate the perfect labyrinthe
 * @param gameboard
 * @param row
 * @param column
 */
void destroy_walls(int **gameboard, int row, int column);

/**
 * This function is writing into a file the actual gameboard
 * @param name the value the user will set to his labyrinthe
 * @param game_board
 * @param row
 * @param column
 */
void print_game_board(char * name,int ** game_board, int row, int column);

/**
 * This function create the labyrinthe by calling all others functions
 * @param game_board
 */
void create_labyrinthe(int **game_board);

/**
 * This function isn't finished yet
 * @param game_board
 */
void load_labyrinthe(int ** game_board);


#endif //PROJET_GAME_BOARD_H