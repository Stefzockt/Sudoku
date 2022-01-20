#include <stdio.h>
int gameField[9][9];

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
    //print the columne number
    printf("   ABC DEF GHI\n");
    for(int x = 0; x < 9; x++){
        if(x%3==0){
            printf("   --- --- ---\n");
        }
        //print the left row number
        printf("%d ", x+1);
        for(int y = 0; y < 9; y++){
            int value = gameField[x][y];
            if(y%3==0){
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

int gameEnded() {
    for(int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            if(gameField[x][y]='*'){
                return 0;
            }else{
                return 1;
            }
        }
    }
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
        if(gameEnded() == 1){
            gameFinished = 1;
        }
        gameFinished = 1;
    }
    printf("Game Finished");
    return 0;
}