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
    int points;
}player;

void move_player_row(game_board *g_b, int coor,player * po_pl){
    if(coor == 1){
        g_b->game_board[po_pl->pos_row-1][po_pl->pos_column] = -1;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = 1;
        po_pl->pos_row--;
    }else{
        g_b->game_board[po_pl->pos_row+1][po_pl->pos_column] = -1;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = 1;
        po_pl->pos_row++;
    }
}

void move_player_col(game_board *g_b, int coor, player * po_pl){
    if (coor == 2){
        g_b->game_board[po_pl->pos_row][po_pl->pos_column+1] = -1;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = 1;
        po_pl->pos_column++;
    }else{
        g_b->game_board[po_pl->pos_row][po_pl->pos_column-1] = -1;
        g_b->game_board[po_pl->pos_row][po_pl->pos_column] = 1;
        po_pl->pos_column--;
    }
}

void less_points(player *po_pl){
    if (po_pl->points - 10 < 0){
        po_pl->points = 0;
    }else{
        po_pl->points -= 10;
    }
}

void move_case_bonus_row(game_board *g_b, int coor, player* po_pl, int next){
    if (g_b->game_board[next][po_pl->pos_column] == 1){
        move_player_row(g_b,coor,po_pl);
        po_pl->points++;
    }else if (g_b->game_board[next][po_pl->pos_column] == -2){
        move_player_row(g_b,coor,po_pl);
        less_points(po_pl);
    }else if(g_b->game_board[next][po_pl->pos_column] == -3){
        move_player_row(g_b,coor,po_pl);
        po_pl->points+=10;
    }else{
        printf("Deplacement impossible \n");
    }
}

void move_case_bonus_col(game_board *g_b, int coor, player* po_pl, int next){
    if (g_b->game_board[po_pl->pos_row][next] == 1){
        move_player_col(g_b,coor,po_pl);
        po_pl->points++;
    }else if (g_b->game_board[po_pl->pos_row][next] == -2){
        move_player_col(g_b,coor,po_pl);
        less_points(po_pl);
    }else if(g_b->game_board[po_pl->pos_row][next] == -3){
        move_player_col(g_b,coor,po_pl);
        po_pl->points+=10;
    }else{
        printf("Deplacement impossible \n");
    }
}

void move_case_available(game_board *g_b, int coor, player* po_pl){
    if(coor == 1){
        move_case_bonus_row(g_b,coor,po_pl,po_pl->pos_row-1);
    }else if (coor == 2){
        move_case_bonus_col(g_b,coor,po_pl,po_pl->pos_column+1);
    }else if (coor == 3){
        move_case_bonus_row(g_b,coor,po_pl,po_pl->pos_row+1);
    }else if (coor == 4){
        move_case_bonus_col(g_b,coor,po_pl,po_pl->pos_column-1);
    }
}

int finish(column_row *col_row,player* pos_play){
    if (pos_play->pos_row == col_row->row-2 && pos_play->pos_column == col_row->col-1){
        return 1;
    }
    return 0;
}

void game_finished(game_board* g_b,player * ply){
    FILE *file;
    file = fopen(g_b->name,"r+");

    printf("Game finished, you have done this labyrinthe in %d steps\n",ply->points);
}

char user_entrance(){
    char enter;
    printf("Veuillez inserer une valeur d'entree pour deplacer le joueur :\n -Z pour le haut\n"
                   "-Q pour la gauche\n-S pour le bas\n -D pour la droite\n");
    scanf("%s",&enter);
    if (enter!='\n'){
        return enter;
    }else{
        enter = user_entrance();
    }
}

void launch_game(game_board *g_b, column_row *col_row) {
    char user_enter;
    int flag = 0;
    player po_pl;
    po_pl.pos_row = 1;
    po_pl.pos_column = 0;
    po_pl.points = 0;
    coordonnees coor;
    coor.north = 1;
    coor.east = 2;
    coor.south = 3;
    coor.west = 4;
    printf("%d by %d\n", col_row->row, col_row->col);
    while(flag == 0) {
        display_game_board(g_b,col_row);
        printf("Score : %d\n",po_pl.points);
        user_enter = user_entrance();
        switch (tolower(user_enter)) {
            case 'z' :
                move_case_available(g_b, coor.north, &po_pl);
                flag = finish(col_row,&po_pl);
                break;
            case 'q' :
                move_case_available(g_b, coor.west, &po_pl);
                flag = finish(col_row,&po_pl);
                break;
            case 's' :
                move_case_available(g_b, coor.south, &po_pl);
                flag = finish(col_row,&po_pl);
                break;
            case 'd' :
                move_case_available(g_b, coor.east, &po_pl);
                flag = finish(col_row,&po_pl);
                break;
            default:break;
        }
    }
    game_finished(g_b,&po_pl);
}

void game_menu(){
    int flag = 0;
    int answer;
    int game_in = 0;
    game_board g_b;
    g_b.name = malloc(sizeof(char*));
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
                printf("Afin de pouvoir continuer vous devez créer un labyrinthe. Par exemple 9 par 23 \n");
                create_labyrinthe(&g_b,&col_row);
                game_in = 1;
            }
        }else{
            flag = 1;
        }
    }
    free_game_board(&g_b);
}

