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
* @file game.h
* Links all the functions of the the game.c
*/

#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <mem.h>

typedef struct{
    int pos_column;
    int pos_row;
    int points;
}player;

#ifndef PROJET_GAME_H
#define PROJET_GAME_H

/**
 * This function move the player in row
 * @param g_b the structure game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 */
void move_player_row(game_board *g_b, int coor, player * po_pl);

/**
 * This function move the player in column
 * @param g_b the structure game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 */
void move_player_col(game_board *g_b, int coor, player * po_pl);

/**
 * This function permit to set the number of player to 0 when he get a bonus which get his points under 0
 * @param po_pl structure of the player
 */
void less_points(player *po_pl);

/**
 * This function is used by the move_case_available for moving the position of the player on row
 * @param g_b the structure of the game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 * @param next the next case of the game board the user want to move
 */
void move_case_bonus_row(game_board *g_b, int coor, player* po_pl, int next);

/**
 * This function is used by the move_case_available for moving the position of the player on column
 * @param g_b the structure of the game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 * @param next the next case of the game board the user want to move
 */
void move_case_bonus_col(game_board *g_b, int coor, player* po_pl, int next);

/**
 * This function move the player in function of the direction the user choose
 * @param g_b the structure of the game board
 * @param coor the coordinated direction of the movement of the user
 * @param po_pl the structure of the player
 */
void move_case_available(game_board *g_b, int coor, player* po_pl);

/**
 * This function looks if the user have finished the game or not in function of his position
 * @param po_play the structure of the player
 * @return 1 if the user won 0 if it isn't finished
 */
int finish(game_board * g_b, player* po_play);

/**
 * This function launch's if the number of pseudo names in the file of the <labyrinth>.score = 10
 * If then so the last number of points is replaced by the current score done by the user
 * @param pseudo the pseudo of the current player
 * @param scoring the scoring of all the players
 * @param f the file .score we are looking for
 * @param array_pseudo the array of all the pseudos registered
 * @param ply the structure of the player
 * @param name_file is the name of the file which we will overprint
 */
void max_pseudo_file_fill(char pseudo[100], int scoring[10][1], FILE * f,char array_pseudo[10][100], player * ply,
        char * name_file);

/**
 * This function is launched when the game is finished. If the user have finished the game
 * @param g_b the structure of the game board
 * @param ply the structure of the player
 */
void game_finished(game_board* g_b,player * ply);

/**
 * This function return the entrance of the user for the movement of the player
 * q for left d for right z for top and s for bottom
 * @return the direction of the user
 */
char user_entrance();

/**
 * This function launch's the game with the last game board entered of the user
 * @param g_b the structure of the game board
 */
void launch_game(game_board * g_b);

/**
 * This function ask for the pseudo of the user
 * @param pseudo to enter by the user
 */
void enter_pseudo(char pseudo[100]);

/**
 * This function launch the principal menu of the game
 */
void game_menu();
#endif //PROJET_GAME_H
