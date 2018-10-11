//
// Created by arist on 08/10/2018.
//

#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "game_board.h"
typedef struct{
    int pos_column;
    int pos_row;
}position_player;

void move_case_available(game_board *g_b, int coor, position_player* po_pl){
    if(coor == 1){
        if (g_b->game_board[po_pl->pos_column-1][po_pl->pos_row] == 1){
            g_b->game_board[po_pl->pos_column-1][po_pl->pos_row] = -1;
            g_b->game_board[po_pl->pos_column][po_pl->pos_row] = 1;
            po_pl->pos_column--;
        }
    }else if (coor == 2){
        if (g_b->game_board[po_pl->pos_column][po_pl->pos_row+1] == 1){
            g_b->game_board[po_pl->pos_column][po_pl->pos_row+1] = -1;
            g_b->game_board[po_pl->pos_column][po_pl->pos_row] = 1;
            po_pl->pos_row++;
        }
    }else if (coor == 3){
        if (g_b->game_board[po_pl->pos_column+1][po_pl->pos_row] == 1){
            g_b->game_board[po_pl->pos_column+1][po_pl->pos_row] = -1;
            g_b->game_board[po_pl->pos_column][po_pl->pos_row] = 1;
            po_pl->pos_column++;
        }
    }else if (coor == 4){
        if (g_b->game_board[po_pl->pos_column][po_pl->pos_row-1] == 1){
            g_b->game_board[po_pl->pos_column][po_pl->pos_row-1] = -1;
            g_b->game_board[po_pl->pos_column][po_pl->pos_row] = 1;
            po_pl->pos_row--;
        }
    }
}

int finish(column_row *col_row,position_player* pos_play){
    if (pos_play->pos_row == col_row->row && pos_play->pos_column == col_row->col-1){
        return 1;
    }
    return 0;
}

void launch_game(game_board *g_b, column_row *col_row) {
    int user_enter;
    int flag = 0;
    position_player *po_pl = malloc(sizeof(position_player));
    po_pl->pos_column = 1;
    po_pl->pos_row = 0;
    coordonnees coor;
    coor.north = 1;
    coor.east = 2;
    coor.south = 3;
    coor.west = 4;
    printf("%d by %d", col_row->row, col_row->col);
    while(flag == 0) {
        display_game_board(g_b,col_row);
        printf("Veuillez insérer une valeur d'entrée pour déplacer le joueur : -Z pour le haut\n"
                       "-Q pour la gauche\n-S pour le bas\n -D pour la droite\n");
        scanf("%d",&user_enter);
        switch (tolower(user_enter)) {
            case 'z' :
                move_case_available(g_b, coor.north, po_pl);
                flag = finish(col_row,po_pl);
                break;
            case 'q' :
                move_case_available(g_b, coor.west, po_pl);
                flag = finish(col_row,po_pl);
                break;
            case 's' :
                move_case_available(g_b, coor.south, po_pl);
                flag = finish(col_row,po_pl);
                break;
            case 'd' :
                move_case_available(g_b, coor.east, po_pl);
                flag = finish(col_row,po_pl);
                break;
        }
    }
    free(po_pl);
}

void game_menu(){
    int flag = 0;
    int answer;
    int game_in = 0;
    game_board g_b;
    column_row col_row;
    while(flag != 1){
        printf("Bonjour et bienvenue sur le labyrinthe de l'ensi. Afin de continuer veuillez selectionner une option : \n");
        printf("Pour creer un labyrinthe -> 1\n");
        printf("Pour charger un labyrinthe -> 2\n");
        printf("Pour Jouer au labyrinthe -> 3\n");
        printf("Pour Quitter -> 4\n");
        scanf("%d",&answer);
        if (answer == 1){
            create_labyrinthe(&g_b,&col_row);
            game_in = 1;
        }else if(answer == 2){
            load_labyrinthe(&g_b,&col_row);
            game_in = 1;
        }else if(answer == 3){
            if(game_in == 1){
                launch_game(&g_b,&col_row);
            }else{
                printf("Afin de pouvoir continuer vous devez créer un labyrinthe. Par exemple 9 par 23");
                create_labyrinthe(&g_b,&col_row);
                game_in = 1;
            }
        }else{
            flag = 1;
        }
    }
    free_game_board(&g_b);
}

