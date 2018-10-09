//
// Created by arist on 08/10/2018.
//


#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

typedef struct{
    int north;
    int east;
    int south;
    int west;
}coordonnees;

typedef struct{
    int row;
    int col;
}column_row;

void display_game_board(int **game_board, int row, int column){
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (game_board[i][j] == 0){
                printf("#");
            }else if (game_board[i][j] == 1){
                printf(" ");
            }else if(game_board[i][j] == -1){
                printf("%c",111);
            }else{
                printf("%d",game_board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void display_game_board_no_filter(int **game_board, int row, int column){
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            printf("%d",game_board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int enter_odd(){
    int number;
    scanf("%d",&number);
    if(number%2 == 0 || number <= 0){
        printf("Saisie fausse votre chiffre n'est pas impair\n");
        number = enter_odd();
    }else{
        return number;
    }

}
void init_game_board(int **game_board, int row, int column){
    int count = 0;
    int entrance = 1;
    int exit = row-2;
    game_board[entrance][0] = -1;
    game_board[exit][column-1] = 1;
    for (int i = 1; i < row - 1; i += 2) {
        for (int j = 1; j < column - 1; j  += 2) {
            game_board[i][j] = ++count ;
        }
    }
}
void destroy_game_board(int **game_board){
    for (int j = 0; j < sizeof(game_board); ++j) {
        free(game_board[j]);
    }
    free(game_board);
}

int fill_rand(int random_y_x, int pos_x, int pos_y,int row, int column){
    coordonnees coor;
    coor.north = 1;
    coor.east = 2;
    coor.south = 3;
    coor.west = 4;
    int last_empty_case_y = row - 2;
    int last_empty_case_x = column - 2;
    // 1 -> haut
    // 2 -> droite
    // 3 -> bas
    // 4 -> gauche
    // Pour le bas
    if(pos_x == last_empty_case_y) {
        if (random_y_x == coor.south){ // gestion pour le bas et bas/gauche et bas/droite
            random_y_x -= 2;
        }else if (pos_y == 1 && random_y_x == coor.west){
            random_y_x -= 2;
        }else if(pos_y == last_empty_case_x && random_y_x == coor.east){
            random_y_x += 2;
        }
    }else if (pos_x == 1) { // gestion pour le haut et haut/gauche et haut/droite
        if (random_y_x == coor.north){
            random_y_x += 2;
        }else if(pos_y == 1 && random_y_x == coor.west){
            random_y_x -=2;
        }else if(pos_y == last_empty_case_x && random_y_x == coor.east){
            random_y_x += 2;
        }
    }else if (pos_y == 1 && random_y_x == coor.west){ // gestion pour la gauche
        random_y_x -= 2;
    }else if(pos_y == last_empty_case_x && random_y_x == coor.east){ // gestion pour la droite
        random_y_x += 2;
    }
    return random_y_x;
}

int verify_arrays(int **game_board,int row, int column){
    for (int i = 1; i <= row - 1; i+= 2) {
        for (int j = 1; j <= column - 1; j += 2) {
            if (game_board[i][j] != 1) {
                return 0;
            }
        }
    }
    return 1;
}

void change_valeur(int **gameboard,int val, int replace, int row, int column){
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < column - 1; j ++) {
            if (gameboard[i][j] == val) {
                gameboard[i][j] = replace;
            }
        }
    }
}

int verif_random(int random[],int seek){
    for (int i = 0; i < sizeof(random); ++i) {
        if (random[i] == seek) {
            return 0;
        }
    }
    return 1;
}

int rand_a_b(int a, int b){
    return rand()%(b-a)+a;
}

void false_random(int taille, int random[]){
    int n = taille*2-3;
    int temp;
    for (int i = 0; i < n; ++i) {
        int flag = 0;
        while(flag != 1) {
            temp = rand_a_b(1,44);
            if (verif_random(random,temp) == 1){
                flag = 1;
                random[i] = temp;
            }
        }
    }
}

void test_destroy_y(int random_y_x,int ** gameboard,int pos_y, int pos_x,int fact, int row, int column){
    int temp;
    if(gameboard[pos_y][pos_x] != gameboard[fact][pos_x]){
        if(gameboard[pos_y][pos_x] < gameboard[fact][pos_x]){
            temp = gameboard[pos_y][pos_x];
            change_valeur(gameboard,gameboard[fact][pos_x],gameboard[pos_y][pos_x],row,column);
        }else{
            temp = gameboard[fact][pos_x];
            change_valeur(gameboard,gameboard[pos_y][pos_x],gameboard[fact][pos_x],row,column);
        }
        if (random_y_x == 1) {
            gameboard[pos_y-1][pos_x] = temp;
        }else{
            gameboard[pos_y+1][pos_x] = temp;
        }
    }
}

void test_destroy_x(int random_y_x,int ** gameboard,int pos_y, int pos_x, int fact, int row, int column){
    int temp;
    if(gameboard[pos_y][pos_x] != gameboard[pos_y][fact]){
        if(gameboard[pos_y][pos_x] < gameboard[pos_y][fact]){
            temp = gameboard[pos_y][pos_x];
            change_valeur(gameboard,gameboard[pos_y][fact],gameboard[pos_y][pos_x],row,column);
        }else{
            temp = gameboard[pos_y][fact];
            change_valeur(gameboard,gameboard[pos_y][pos_x],gameboard[pos_y][fact],row,column);
        }
        if (random_y_x == 4) {
            gameboard[pos_y][pos_x-1] = temp;
        }else{
            gameboard[pos_y][pos_x+1] = temp;
        }
    }
}

void destroy_walls(int **gameboard, int row, int column){
    int random;
    int empty_cases = ((row-1)*(column-1))/4;
    // 1 -> haut
    // 2 -> droite
    // 3 -> bas
    // 4 -> gauche
    int random_y_x;
    int flag = 0;
    int count;
    int i;
    while(flag == 0){
        random = rand_a_b(1,empty_cases);
        count = 0;
        for (i = 1; i < row-1; i+= 2) {
            for (int j = 1; j < column-1; j+= 2) {
                count++;
                if(random == count){
                    random_y_x = rand()%4+1; // générateur de random sur une plage de 1 à 4
                    random_y_x = fill_rand(random_y_x,i,j,row,column);
                    if (random_y_x == 1){ //suppression du mur du haut
                        test_destroy_y(random_y_x,gameboard,i,j,i-2,row,column);
                    }else if (random_y_x == 2){ //suppression du mur de droite
                        test_destroy_x(random_y_x,gameboard,i,j,j+2,row,column);
                    }else if(random_y_x == 3) { //suppression du mur du bas
                        test_destroy_y(random_y_x,gameboard,i,j,i+2,row,column);
                    }else if (random_y_x == 4){ //suppression du mur de gauche
                        test_destroy_x(random_y_x,gameboard,i,j,j-2,row,column);
                    }
                }
            }
        }
        flag = verify_arrays(gameboard,row,column);
    }
}

void print_game_board(char * name,int ** game_board, int row, int column){
    name = strcat(name,".cfg");
    FILE * file = fopen(name,"w");
    int count = 0;
    if (file != NULL) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (game_board[i][j] == 0){
                    fputc('#',file);
                }else if (game_board[i][j] == 1){
                    fputc(' ',file);
                }else if(game_board[i][j] == -1){
                    fputc('o',file);
                }
                count++;
            }
            fputc('\n',file);
        }
        fclose(file);
    }
}

void create_labyrinthe(int **game_board){
    int y;
    int x;
    char * name = (char *) malloc(sizeof(char));
    printf("Vous avez selectionne la creation de tableau.\n");
    printf("Veuillez saisir un premier nombre IMPAIR qui sera votre hauteur : ");
    y = enter_odd();
    printf("Veuillez saisir un second nombre IMPAIR qui sera votre longueur : ");
    x = enter_odd();

    column_row co_row;
    co_row.row = x;
    co_row.col = y;

    game_board = calloc(co_row.col,sizeof(int*));
    for (int i = 0; i < y; ++i) {
        game_board[i] = calloc(co_row.row,sizeof(int));
    }
    init_game_board(game_board,co_row.col,co_row.row);
    display_game_board(game_board,co_row.col,co_row.row);

    destroy_walls(game_board,co_row.col,co_row.row);
    display_game_board(game_board,co_row.col,co_row.row);

    printf("Votre labyrinthe a ete cree\nVeuillez saisir un nom a votre labyrinthe : ");
    scanf("%s",name);
    print_game_board(name,game_board,co_row.col,co_row.row);
    free(name);
}

void load_labyrinthe(int ** game_board){
    char * name = (char*) malloc(sizeof(char));
    FILE * file;
    char * line = (char*) malloc(sizeof(char));
    printf("Veuillez saisir la localisation de votre fichier : ");
    scanf("%s",name);
    file = fopen(name,"r");
    int y = 0;
    int x = 0;
    if (file != NULL){
        while (fgetc(file) != NULL){
            if (fgetc(file)== '#'){
                game_board[y][x] = 0;
                x++;
            }else if (fgetc(file) == ' '){
                game_board[y][x] = 1;
                x++;
            }else if(fgetc(file) == 'o'){
                game_board[y][x] = -1;
                x++;
            }else if(fgetc(file) == '\n'){
                y++;
            }
        }
        fclose(file);
    }

    free(name);
}