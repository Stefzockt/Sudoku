#include <stdio.h>
#include <math.h>
#include <ctype.h>

int gameField[9][9];
#define LENGTH(array) (sizeof(array)/sizeof(array[0]))

// 0 equals false
// 1 equals true

void setGameField() {
    for (int x =0;x <= 9; x++) {
        for(int y =0; y<=9; y++){
            gameField[x][y] = 0;
        }
    }
}


void Draw(char playerName[]){
    printf("Player: %s\n", playerName);

    printf("   ABC DEF GHI\n");
    for(int i = 0; i < 9; i++){
        if(i%3==0){
            printf("   --- --- ---\n");
        }

        printf("%d ", i+1); // line numbers
        for(int j = 0; j < 9; j++){
            int value = gameField[i][j];
            if(j%3==0){
                printf("|");
            }
            if(value == 0){
                printf("*");
            } else {
                printf("%d", value);
            }
        }
        printf("|\n");
    }
    printf("   --- --- ---\n");
}

int main() {
    int gameFinished = 0;
    char playerName[15]={};
    setGameField();
    printf("Please enter your name:");
    scanf("%20s", playerName);

    //This will go one as long as the game is not finished
    while (0 == gameFinished){
        Draw(playerName);
        gameFinished = 1;
    }
    printf("Game Finished");
    return 0;
}