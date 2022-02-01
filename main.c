#include <stdio.h>
#include <ctype.h>
// 0 equals false
// 1 equals true

#define LEN(array) (sizeof(array)/sizeof(array[0])) //This gets us the Length of any Array we put in

//Globals
int gameField[9][9];
static char alphabet[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};


void generateSudoku() {

}


//All Rules
int isValueInColumn (int row, int column, int value){
    for (int i = 0; i < 9; i++){
        if (value == gameField[i][column]) {
            printf("The Value %d is already in the column!\n",value);
            return 1;
        }
    }
    return 0;
}

int isValueInRow (int row, int column, int value){
    for (int i = 0; i < 9; i++){
        if (value == gameField[row][i]) {
            printf("The Value %d is already in the row!\n",value);
            return 1;
        }
    }
    return 0;
}

int isValueInBox(int row, int column, int value){
    int localBoxRow = row - row % 3;
    int localBoxColumn = column - column % 3;
    for (int i = localBoxRow; i < localBoxRow + 3; i++){
        for (int j = localBoxColumn; j < localBoxColumn + 3; j++){
            if (gameField[i][j] == value){
                printf("The Value %d is already in this Box!\n",value);
                return 1;
            }
        }
    }
    return 0;
}

//If the value is checks all rules a 1 is given back
int checkAllRules(int row, int column, int value){
    if (isValueInRow(row,column,value) == 0 && isValueInColumn(row,column,value) == 0 && isValueInBox(row,column,value) == 0){
        return 1;
    }
    return 0;
}


//Fills the gameField Array with 0
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
//Checks if the Array contains a 0. If not it will return 1.
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
    int inputValue;

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
        if (scanf("%c%d%d",&column,&row,&inputValue) != 2 || inputValue != '\n')
        getchar();

        //Check if the input is correct
        if (inputValue <= 9 && inputValue > 0){
            if (row <= 9 && row > 0){
                row--; //We start counting from zero and the sudoku starts from 1 so we need to subtract 1.
                if(tolower(column) <= 'i'){
                    //We will go through our alphabet Array and set the value i to the position where the character from the column is.
                    for (int columnInt = 0; columnInt < LEN(alphabet); columnInt++){
                        if (toupper(column) == alphabet[columnInt]){
                            if (checkAllRules(row, columnInt, inputValue) == 1){
                                gameField[row][columnInt] = inputValue;//Put the value into the Array if all Values are Correct and the rules are checked
                            }
                        }
                    }
                } else {
                    printf("Incorrect column: %c\n",column);
                }
            } else {
                printf("Incorrect row: %d\n",row);
            }
        }else{
            printf("Incorrect Value: %d\n" ,inputValue);
        }
    }
    printf("Game Finished");
    return 0;
}