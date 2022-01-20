#include <stdio.h>
#include <ctype.h>

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

void draw(char playerName[]){
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
    int validInput = 0;
    char playerName[20];
    char column;
    int row;
    int inputVal;
    setGameField();
    //If incorrect input ask again
    do{
        printf("Please enter your name:");
    } while (scanf("%s", &playerName) == 0);
    getchar();
    //This will go one as long as the game is not finished
    while (0 == gameFinished){
        draw(playerName);
        printf("Please enter your column then row and then your input value:\n");
        //Check if the input is correct
        while (validInput == 0) {
            scanf("%c%d%d",&column,&row,&inputVal);
            getchar();
            if (inputVal <= 9){
                if (row <= 9){
                    if(tolower(column) <= 'i'){
                        validInput=1;
                    } else {
                        printf("Incorrect column: %c\n",column);
                        printf("Pleas enter again:\n");
                    }
                } else {
                    printf("Incorrect row: %d\n",row);
                    printf("Pleas enter again:\n");
                }
            }else{
                printf("Incorrect inputValue: %d\n",inputVal);
                printf("Pleas enter again:\n");
            }
        }

        printf("%c %d %d\n",column,row,inputVal);


        if(gameEnded() == 1){
            gameFinished = 1;
        }
        gameFinished = 1;
    }
    printf("Game Finished");
    return 0;
}