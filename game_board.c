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

typedef struct{
    int **game_board;
}game_board;

void display_game_board(game_board *g_b, column_row* col_row){
    for (int i = 0; i < col_row->row; ++i) {
        for (int j = 0; j < col_row->col; ++j) {
            if (g_b->game_board[i][j] == 0){
                printf("#");
            }else if (g_b->game_board[i][j] == 1){
                printf(" ");
            }else if(g_b->game_board[i][j] == -1){
                printf("%c",111);
            }else{
                printf("%d",g_b->game_board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void display_game_board_no_filter(game_board *g_b, column_row* col_row){
    for (int i = 0; i < col_row->row; ++i) {
        for (int j = 0; j < col_row->col; ++j) {
            printf("%d",g_b->game_board[i][j]);
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
void init_game_board(game_board *g_b, column_row* col_row){
    int count = 0;
    int entrance = 1;
    int exit = col_row->row-2;
    g_b->game_board[entrance][0] = -1;
    g_b->game_board[exit][col_row->col-1] = 1;
    for (int i = 1; i < col_row->row - 1; i += 2) {
        for (int j = 1; j < col_row->col - 1; j  += 2) {
            g_b->game_board[i][j] = ++count ;
        }
    }
}
void free_game_board(game_board *g_b){
    for (int j = 0; j < sizeof(game_board); ++j) {
        free(g_b->game_board[j]);
    }
    free(g_b->game_board);
}

int fill_rand(int random_y_x, int pos_x, int pos_y, column_row* col_row){
    coordonnees coor;
    coor.north = 1;
    coor.east = 2;
    coor.south = 3;
    coor.west = 4;
    int last_empty_case_y = col_row->row - 2;
    int last_empty_case_x = col_row->col - 2;
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

int verify_arrays(game_board *g_b, column_row* col_row){
    for (int i = 1; i <= col_row->row - 1; i+= 2) {
        for (int j = 1; j <= col_row->col - 1; j += 2) {
            if (g_b->game_board[i][j] != 1) {
                return 0;
            }
        }
    }
    return 1;
}

void change_valeur(game_board *g_b,int val, int replace, column_row* col_row){
    for (int i = 1; i < col_row->row - 1; i++) {
        for (int j = 1; j < col_row->col - 1; j ++) {
            if (g_b->game_board[i][j] == val) {
                g_b->game_board[i][j] = replace;
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

void test_destroy_y(int random_y_x,game_board *g_b,int pos_y, int pos_x,int fact, column_row* col_row){
    int temp;
    if(g_b->game_board[pos_y][pos_x] != g_b->game_board[fact][pos_x]){
        if(g_b->game_board[pos_y][pos_x] < g_b->game_board[fact][pos_x]){
            temp = g_b->game_board[pos_y][pos_x];
            change_valeur(g_b,g_b->game_board[fact][pos_x],g_b->game_board[pos_y][pos_x],col_row);
        }else{
            temp = g_b->game_board[fact][pos_x];
            change_valeur(g_b,g_b->game_board[pos_y][pos_x],g_b->game_board[fact][pos_x],col_row);
        }
        if (random_y_x == 1) { // top
            g_b->game_board[pos_y-1][pos_x] = temp;
        }else{ // bot
            g_b->game_board[pos_y+1][pos_x] = temp;
        }
    }
}

void test_destroy_x(int random_y_x,game_board *g_b,int pos_y, int pos_x, int fact, column_row* col_row){
    int temp;
    if(g_b->game_board[pos_y][pos_x] != g_b->game_board[pos_y][fact]){
        if(g_b->game_board[pos_y][pos_x] < g_b->game_board[pos_y][fact]){
            temp = g_b->game_board[pos_y][pos_x];
            change_valeur(g_b,g_b->game_board[pos_y][fact],g_b->game_board[pos_y][pos_x],col_row);
        }else{
            temp = g_b->game_board[pos_y][fact];
            change_valeur(g_b,g_b->game_board[pos_y][pos_x],g_b->game_board[pos_y][fact],col_row);
        }
        if (random_y_x == 4) { // left
            g_b->game_board[pos_y][pos_x-1] = temp;
        }else{ // right
            g_b->game_board[pos_y][pos_x+1] = temp;
        }
    }
}

void destroy_walls(game_board *g_b, column_row* col_row){
    int random;
    int empty_cases = ((col_row->row-1)*(col_row->col-1))/4;
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
        for (i = 1; i < col_row->row-1; i+= 2) {
            for (int j = 1; j < col_row->col-1; j+= 2) {
                count++;
                if(random == count){
                    random_y_x = rand()%4+1; // générateur de random sur une plage de 1 à 4
                    random_y_x = fill_rand(random_y_x,i,j,col_row);
                    if (random_y_x == 1){ //suppression du mur du haut
                        test_destroy_y(random_y_x,g_b,i,j,i-2,col_row);
                    }else if (random_y_x == 2){ //suppression du mur de droite
                        test_destroy_x(random_y_x,g_b,i,j,j+2,col_row);
                    }else if(random_y_x == 3) { //suppression du mur du bas
                        test_destroy_y(random_y_x,g_b,i,j,i+2,col_row);
                    }else if (random_y_x == 4){ //suppression du mur de gauche
                        test_destroy_x(random_y_x,g_b,i,j,j-2,col_row);
                    }
                }
            }
        }
        flag = verify_arrays(g_b,col_row);
    }
}

void print_file_game_board(char * name,game_board *g_b, column_row* col_row){
    name = strcat(name,".cfg");
    FILE * file = fopen(name,"w");
    int count = 0;
    if (file != NULL) {
        //fprintf(file,"%d*%d\n",row,col);
        for (int i = 0; i < col_row->row; ++i) {
            for (int j = 0; j < col_row->col; ++j) {
                if (g_b->game_board[i][j] == 0){
                    fputc('#',file);
                }else if (g_b->game_board[i][j] == 1){
                    fputc(' ',file);
                }else if(g_b->game_board[i][j] == -1){
                    fputc('o',file);
                }
                count++;
            }
            fputc('\n',file);
        }
        fclose(file);
    }
}

void create_labyrinthe(game_board *g_b, column_row *col_row){
    int y;
    int x;
    char * name = (char *) malloc(sizeof(char));
    printf("Vous avez selectionne la creation de tableau.\n");
    printf("Veuillez saisir un premier nombre IMPAIR qui sera votre hauteur : ");
    y = enter_odd();
    printf("Veuillez saisir un second nombre IMPAIR qui sera votre longueur : ");
    x = enter_odd();

    col_row->col = x;
    col_row->row = y;

    g_b->game_board = calloc(col_row->row,sizeof(int*));
    for (int i = 0; i < y; ++i) {
        g_b->game_board[i] = calloc(col_row->col,sizeof(int));
    }
    init_game_board(g_b,col_row);
    display_game_board(g_b,col_row);

    destroy_walls(g_b,col_row);
    display_game_board(g_b,col_row);

    printf("Votre labyrinthe a ete cree\nVeuillez saisir un nom a votre labyrinthe : ");
    scanf("%s",name);
    print_file_game_board(name,g_b,col_row);
    free(name);
}

void load_labyrinthe(game_board *g_b,column_row *col_row){
    char * name = (char*) malloc(sizeof(char));
    FILE * file;
    char * line = (char*) malloc(sizeof(char));
    printf("Veuillez saisir la localisation de votre fichier : ");
    scanf("%s",name);
    file = fopen(name,"r");

    col_row->row = 0;
    col_row->col = 0;
    int c;
    if (file != NULL){
        while((c = fgetc(file))!= EOF){
            if (c == '\n'){
                col_row->row++;
            }else if(col_row->row == 0){
                col_row->col++;
            }
        }
        printf("%d by %d\n",col_row->row,col_row->col);
        fseek(file,0,0);

        g_b->game_board = calloc(col_row->col,sizeof(int*));
        for (int i = 0; i < col_row->col; ++i) {
            g_b->game_board[i] = calloc(col_row->row,sizeof(int));
        }
        int i = 0;
        int j = 0;
        while ((c = fgetc(file))!= EOF){
            if (c == '#'){
                g_b->game_board[i][j] = 0;
                j++;
            }else if (c == ' '){
                g_b->game_board[i][j] = 1;
                j++;
            }else if(c == 'o'){
                g_b->game_board[i][j] = -1;
                j++;
            }else if(c == '\n'){
                i++;
                j = 0;
            }
        }
        display_game_board(g_b,col_row);
        fclose(file);
    }else{
        printf("Le fichier %s selectionné est introuvable",name);
    }
    free(line);
    free(name);
}