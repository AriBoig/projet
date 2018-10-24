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
* @file game.c
* This file use all the functions to make the program working well thanks to the interaction of the user
*/
#include "game_board.h"
#include "game.h"

/**
 * This function move the player in row
 * @param g_b the structure game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 */
void move_player_row(game_board *g_b, int coor, player * po_pl) {
    if (coor == NORTH) {
        g_b->game_board[po_pl->pos_row-1][po_pl->pos_column] = PLAYER;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = BLANK;
        po_pl->pos_row--;
    } else {
        g_b->game_board[po_pl->pos_row+1][po_pl->pos_column] = PLAYER;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = BLANK;
        po_pl->pos_row++;
    }
}

/**
 * This function move the player in column
 * @param g_b the structure game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 */
void move_player_col(game_board *g_b, int coor, player * po_pl) {
    if (coor == EAST) {
        g_b->game_board[po_pl->pos_row][po_pl->pos_column+1] = PLAYER;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = BLANK;
        po_pl->pos_column++;
    } else {
        g_b->game_board[po_pl->pos_row][po_pl->pos_column-1] = PLAYER;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = BLANK;
        po_pl->pos_column--;
    }
}

/**
 * This function permit to set the number of player to 0 when he get a bonus which get his points under 0
 * @param po_pl structure of the player
 */
void less_points(player *po_pl) {
    if (po_pl->points - 10 < 0) {
        po_pl->points = 0;
    } else {
        po_pl->points -= 10;
    }
}

/**
 * This function is used by the move_case_available for moving the position of the player on row
 * @param g_b the structure of the game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 * @param next the next case of the game board the user want to move
 */
void move_case_bonus_row(game_board *g_b, int coor, player* po_pl, int next) {
    if (g_b->game_board[next][po_pl->pos_column] == BLANK) {
        move_player_row(g_b,coor,po_pl);
        po_pl->points++;
    } else if (g_b->game_board[next][po_pl->pos_column] == BONUS) {
        move_player_row(g_b,coor,po_pl);
        less_points(po_pl);
    } else if(g_b->game_board[next][po_pl->pos_column] == MALUS) {
        move_player_row(g_b,coor,po_pl);
        po_pl->points+=10;
    } else {
        printf("Movement impossible \n");
    }
}

/**
 * This function is used by the move_case_available for moving the position of the player on column
 * @param g_b the structure of the game board
 * @param coor the coordinated direction of the movement
 * @param po_pl the structure of the player
 * @param next the next case of the game board the user want to move
 */
void move_case_bonus_col(game_board *g_b, int coor, player* po_pl, int next) {
    if (g_b->game_board[po_pl->pos_row][next] == BLANK) {
        move_player_col(g_b,coor,po_pl);
        po_pl->points++;
    } else if (g_b->game_board[po_pl->pos_row][next] == BONUS) {
        move_player_col(g_b,coor,po_pl);
        less_points(po_pl);
    } else if(g_b->game_board[po_pl->pos_row][next] == MALUS) {
        move_player_col(g_b,coor,po_pl);
        po_pl->points+=10;
    } else {
        printf("Movement impossible \n");
    }
}

/**
 * This function move the player in function of the direction the user choose
 * @param g_b the structure of the game board
 * @param coor the coordinated direction of the movement of the user
 * @param po_pl the structure of the player
 */
void move_case_available(game_board *g_b, int coor, player* po_pl) {
    if (coor == 1) {
        move_case_bonus_row(g_b,coor,po_pl,po_pl->pos_row-1);
    } else if (coor == 2) {
        move_case_bonus_col(g_b,coor,po_pl,po_pl->pos_column+1);
    }else if (coor == 3) {
        move_case_bonus_row(g_b,coor,po_pl,po_pl->pos_row+1);
    } else if (coor == 4) {
        move_case_bonus_col(g_b,coor,po_pl,po_pl->pos_column-1);
    }
}

/**
 * This function looks if the user have finished the game or not in function of his position
 * @param po_play the structure of the player
 * @return 1 if the user won 0 if it isn't finished
 */
int finish(game_board * g_b, player* po_play) {
    if (po_play->pos_row == g_b->row-2 && po_play->pos_column == g_b->col-1) {
        return 1;
    }
    return 0;
}

/**
 * This function ask for the pseudo of the user
 * @param pseudo to enter by the user
 */
void enter_pseudo(char pseudo[100]){
    printf("Congratulations, you are classed in the rank of this labyrinth. Please enter your "
           "pseudo name : ");
    scanf("%s",pseudo);
}

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
        char * name_file) {
    enter_pseudo(pseudo);
    int temp_max = scoring[0][0];
    int flag2 = 0;
    for (int g = 1; g < 10; ++g) {
        if (scoring[g][0] > temp_max){
            temp_max = scoring[g][0];
        }
    }
    for (int j = 0; j < 10; ++j) {
        if (scoring[j][0] == temp_max && flag2 == 0){
            scoring[j][0] = ply->points;
            strcpy(array_pseudo[j],pseudo);
            flag2 = 1;
        }
    }
    fclose(f);
    f = fopen(name_file,"w");
    for (int k = 0; k < 10; ++k) {
        fprintf(f,"%s %d\n",array_pseudo[k],scoring[k][0]);
    }
}

/**
 * This function is launched when the game is finished. If the user have finished the game
 * @param g_b the structure of the game board
 * @param ply the structure of the player
 */
void game_finished(game_board* g_b,player * ply) {
    FILE * f;
    char * name_file = NULL;
    char * line = malloc(sizeof(char*));
    char pseudo[100];
    int scoring[10][1];
    char array_pseudo[10][100];
    int flag = 0;
    name_file = malloc(strlen(g_b->name)+5);
    name_file[0] = '\0';
    strcat(name_file,g_b->name);
    strcat(name_file,".score");
    f = fopen(name_file,"r+");
    printf("Game finished, you have done this labyrinth with %d points\n",ply->points);
    if (f != NULL) {
        int i = 0;
        while (fscanf(f,"%s %d",array_pseudo[i],scoring[i]) != EOF) {
            if (i < 10 && scoring[i][0] >= ply->points && flag == 0) {
                flag = 1;
            }
            i++;
        }
        if (i < 10) {
            enter_pseudo(pseudo);
            fprintf(f,"\n%s %d", pseudo, ply->points);
        } else if(flag == 1 && i == 10) {
            max_pseudo_file_fill(pseudo,scoring,f,array_pseudo,ply,name_file);
        }
    } else {
        printf("There is no file from scores with this name of labyrinth. Please enter your pseudo name : ");
        scanf("%s",pseudo);
        f = fopen(name_file,"w");
        fprintf(f,"%s %d",pseudo,ply->points);
    }
    fclose(f);
    free(name_file);
    free(line);
}

/**
 * This function return the entrance of the user for the movement of the player
 * q for left d for right z for top and s for bottom
 * @return the direction of the user
 */
char user_entrance() {
    char enter;
    printf(" Please insert a value for moving the player :\n -Z For the top\n"
                   " -Q for the left\n -S for the bottom\n -D for the right\n");
    scanf("%s",&enter);
    if (enter!='\n' || enter == 'q' || enter == 's' || enter == 'd' || enter == 'z') {
        return enter;
    } else {
        enter = user_entrance();
    }
}

/**
 * This function launch's the game with the last game board entered of the user
 * @param g_b the structure of the game board
 */
void launch_game(game_board *g_b) {
    char user_enter;
    int flag = 0;
    player po_pl;
    po_pl.pos_row = 1;
    po_pl.pos_column = 0;
    po_pl.points = 0;
    printf("%d by %d\n", g_b->row, g_b->col);
    while(flag == 0) {
        display_game_board(g_b);
        printf("Score : %d\n",po_pl.points);
        user_enter = user_entrance();
        switch (tolower(user_enter)) {
            case 'z' :
                move_case_available(g_b, NORTH, &po_pl);
                flag = finish(g_b,&po_pl);
                break;
            case 'q' :
                move_case_available(g_b, WEST, &po_pl);
                flag = finish(g_b,&po_pl);
                break;
            case 's' :
                move_case_available(g_b, SOUTH, &po_pl);
                flag = finish(g_b,&po_pl);
                break;
            case 'd' :
                move_case_available(g_b, EAST, &po_pl);
                flag = finish(g_b,&po_pl);
                break;
            default:break;
        }
    }
    game_finished(g_b,&po_pl);
}

/**
 * This function launch the principal menu of the game
 */
void game_menu() {
    int flag = 0;
    int answer;
    int game_in = 0;
    game_board g_b;
    g_b.name = malloc(sizeof(char*));
    while(flag != 1) {
        printf("#################################################\n");
        printf("#                                               #\n");
        printf("#                    LABYRINTH                  #\n");
        printf("#                                               #\n");
        printf("#################################################\n\n");
        printf("Please select an option : \n");
        printf("For creating a labyrinth -> 1\n");
        printf("For load a labyrinth -> 2\n");
        printf("For playing on a labyrinth -> 3\n");
        printf("Pour quit -> 4\n");
        scanf("%d",&answer);
        if (answer == 1){
            create_labyrinthe(&g_b);
            game_in = 1;
        } else if(answer == 2) {
            printf("Please enter the name of the labyrinth : ");
            scanf("%s",g_b.name);
            load_labyrinthe(&g_b);
            game_in = 1;
        } else if(answer == 3) {
            if(game_in == 1){
                load_labyrinthe(&g_b);
                launch_game(&g_b);
            } else {
                printf("You have to create first a labyrinth \n");
                create_labyrinthe(&g_b);
                game_in = 1;
            }
        } else {
            if (game_in == 1){
                free_game_board(&g_b);
            }else{
                free(g_b.name);
            }
            flag = 1;
        }
    }
}

