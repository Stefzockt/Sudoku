#include <stdio.h>
#include <ctype.h>
// 0 equals false
// 1 equals true

#define LEN(array) (sizeof(array)/sizeof(array[0])) //This gets us the Length of any Array we put in

//Globals
int gameField[9][9];
static char alphabet[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

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
//Checks if the Array has an Input
int gameEnded() {
    for(int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            if(gameField[x][y] == '0'){
                return 0;
            }
        }
    }
    return 1;
}

int main() {
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

    //This will go one as long the game is not finished
    while (1 == gameEnded()){
        draw(playerName);
        printf("Please enter your column then row and then your input value:\n");
        if (scanf("%c%d%d",&column,&row,&inputVal) != 2 || inputVal != '\n');
        getchar();

        //Check if the input is correct
        if (inputVal <= 9 && inputVal > 0){
            if (row <= 9 && row > 0){
                row--; //We start counting from zero and the sudoku starts from 1 so we need to subtract 1.
                if(tolower(column) <= 'i'){
                    for (int i = 0; i < LEN(alphabet); i++){
                        if (toupper(column) == alphabet[i]){
                            gameField[row][i] = inputVal; //Put the value into the Array if all Values are Correct
                        }
                    }
                } else {
                    printf("Incorrect column: %c\n",column);
                }
            } else {
                printf("Incorrect row: %d\n",row);
            }
        }else{
            printf("Incorrect Value: %d\n" ,inputVal);
        }
    }
    printf("Game Finished");
    return 0;
}