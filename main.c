#include <stdio.h>
#include <malloc.h>
#include <mem.h>

void display_game_board(int **game_board, int y, int x){
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
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

void display_game_board_no_filter(int **game_board, int y, int x){
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
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
void init_game_board(int **game_board,int y, int x){
    int count = 0;
    int entrance = 1;
    int exit = y-2;
    game_board[entrance][0] = -1;
    game_board[exit][x-1] = 1;
    for (int i = 1; i < y - 1; i += 2) {
        for (int j = 1; j < x - 1; j  += 2) {
            game_board[i][j] = ++count ;
        }
    }
}
void destroy_game_board(int **game_board, int x){
    for (int j = 0; j < x; ++j) {
        free(game_board[j]);
    }
    free(game_board);
}

int fill_rand(int random_y_x, int i, int j,int y, int x){
    int last_empty_case_y = y - 2;
    int last_empty_case_x = x - 2;
    // 1 -> haut
    // 2 -> droite
    // 3 -> bas
    // 4 -> gauche
    // Pour le bas
    if(i == last_empty_case_y) {
        if (random_y_x == 3){ // gestion pour le bas et bas/gauche et bas/droite
            random_y_x -= 2;
        }else if (j == 1 && random_y_x == 4){
            random_y_x -= 2;
        }else if(j == last_empty_case_x && random_y_x == 2){
            random_y_x += 2;
        }
    }else if (i == 1) { // gestion pour le haut et haut/gauche et haut/droite
        if (random_y_x == 1){
            random_y_x += 2;
        }else if(j == 1 && random_y_x == 4){
            random_y_x -=2;
        }else if(j == last_empty_case_x && random_y_x == 2){
            random_y_x += 2;
        }
    }else if (j == 1 && random_y_x == 4){ // gestion pour la gauche
        random_y_x -= 2;
    }else if(j == last_empty_case_x && random_y_x == 2){ // gestion pour la droite
        random_y_x += 2;
    }
    return random_y_x;
}

int verify_arrays(int **game_board,int y, int x){
    for (int i = 1; i <= y - 1; i+= 2) {
        for (int j = 1; j <= x - 1; j += 2) {
            if (game_board[i][j] != 1) {
                return 0;
            }
        }
    }
    return 1;
}

void change_valeur(int **gameboard,int val, int replace, int y, int x){
    for (int i = 1; i < y - 1; i++) {
        for (int j = 1; j < x - 1; j ++) {
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

void test_destroy_y(int random_y_x,int ** gameboard,int i, int j,int fact, int y, int x){
    int temp;
    if(gameboard[i][j] != gameboard[fact][j]){
        if(gameboard[i][j] < gameboard[fact][j]){
            temp = gameboard[i][j];
            change_valeur(gameboard,gameboard[fact][j],gameboard[i][j],y,x);
        }else{
            temp = gameboard[fact][j];
            change_valeur(gameboard,gameboard[i][j],gameboard[fact][j],y,x);
        }
        if (random_y_x == 1) {
            gameboard[i-1][j] = temp;
        }else{
            gameboard[i+1][j] = temp;
        }
    }
}

void test_destroy_x(int random_y_x,int ** gameboard,int i, int j,int fact, int y, int x){
    int temp;
    if(gameboard[i][j] != gameboard[i][fact]){
        if(gameboard[i][j] < gameboard[i][fact]){
            temp = gameboard[i][j];
            change_valeur(gameboard,gameboard[i][fact],gameboard[i][j],y,x);
        }else{
            temp = gameboard[i][fact];
            change_valeur(gameboard,gameboard[i][j],gameboard[i][fact],y,x);
        }
        if (random_y_x == 4) {
            gameboard[i][j-1] = temp;
        }else{
            gameboard[i][j+1] = temp;
        }
    }
}

void destroy_walls(int **gameboard, int y, int x){
    int random;
    int empty_cases = ((y-1)*(x-1))/4;
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
        for (i = 1; i < y-1; i+= 2) {
            for (int j = 1; j < x-1; j+= 2) {
                count++;
                if(random == count){
                    random_y_x = rand()%4+1; // générateur de random sur une plage de 1 à 4
                    random_y_x = fill_rand(random_y_x,i,j,y,x);
                    if (random_y_x == 1){ //suppression du mur du haut
                        test_destroy_y(random_y_x,gameboard,i,j,i-2,y,x);
                    }else if (random_y_x == 2){ //suppression du mur de droite
                        test_destroy_x(random_y_x,gameboard,i,j,j+2,y,x);
                    }else if(random_y_x == 3) { //suppression du mur du bas
                        test_destroy_y(random_y_x,gameboard,i,j,i+2,y,x);
                    }else if (random_y_x == 4){ //suppression du mur de gauche
                        test_destroy_x(random_y_x,gameboard,i,j,j-2,y,x);
                    }
                }
            }
        }
        flag = verify_arrays(gameboard,y,x);
    }
}

void print_game_board(char * name,int ** game_board, int y, int x){
    name = strcat(name,".cfg");
    FILE * file = fopen(name,"w");
    int n = x*y;
    int count = 0;
    char to_insert[n];
    if (file != NULL) {
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < x; ++j) {
                to_insert[count] = (char) printf("%d", game_board[i][j]);
                count++;
            }
            count++;
        }
    }
    printf("%s",to_insert);
    fclose(file);
}

void create_labyrinthe(){
    int y;
    int x;
    char * name = (char *) malloc(sizeof(char));
    printf("Vous avez selectionne la creation de tableau.\n");
    printf("Veuillez saisir un premier nombre IMPAIR qui sera votre hauteur : ");
    y = enter_odd();
    printf("Veuillez saisir un second nombre IMPAIR qui sera votre longueur : ");
    x = enter_odd();
    int **game_board;
    game_board = calloc(y,sizeof(int*));
    for (int i = 0; i < y; ++i) {
        game_board[i] = calloc(x,sizeof(int));
    }
    init_game_board(game_board,y,x);
    display_game_board(game_board,y,x);

    destroy_walls(game_board,y,x);
    display_game_board(game_board,y,x);

    printf("Votre labyrinthe a ete cree\nVeuillez saisir un nom a votre labyrinthe : ");
    scanf("%s",name);
    print_game_board(name,game_board,y,x);
    free(name);

    destroy_game_board(game_board,x);
}

void game_menu(){
    int flag = 0;
    int answer;
    while(flag != 1){
        printf("Bonjour et bienvenue sur le labyrinthe de l'ensi. Afin de continuer veuillez selectionner une option : \n");
        printf("Pour creer un labyrinthe -> 1\n");
        printf("Pour charger un labyrinthe -> 2\n");
        printf("Pour Jouer au labyrinthe -> 3\n");
        printf("Pour Quitter -> 4\n");
        scanf("%d",&answer);
        if (answer == 1){
            create_labyrinthe();
        }else if(answer == 2){

        }else if(answer == 3){

        }else{
            flag = 1;
        }
    }
}

int main() {
    game_menu();
    return 0;
}