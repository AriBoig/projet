//
// Created by arist on 08/10/2018.
//


#include <stdio.h>
#include "game_board.h"
void game_menu(){
    int flag = 0;
    int answer;
    int ** game_board;
    while(flag != 1){
        printf("Bonjour et bienvenue sur le labyrinthe de l'ensi. Afin de continuer veuillez selectionner une option : \n");
        printf("Pour creer un labyrinthe -> 1\n");
        printf("Pour charger un labyrinthe -> 2\n");
        printf("Pour Jouer au labyrinthe -> 3\n");
        printf("Pour Quitter -> 4\n");
        scanf("%d",&answer);
        if (answer == 1){
            create_labyrinthe(game_board);
        }else if(answer == 2){
            load_labyrinthe(game_board);
        }else if(answer == 3){

        }else{
            flag = 1;
        }
    }
    destroy_game_board(game_board);
}

