#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
// 0 equals false
// 1 equals true

#define LEN(array) (sizeof(array)/sizeof(array[0])) //This gets us the Length of any Array we put in

//Globals
int gameField[9][9] = {0};
static char alphabet[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

//Generates a random Number between 1-81
int randomGenerator81(){
    return (rand() % 81) + 1;
}

//Generates a random Number between 1-9
int randomGenerator(){
    return (rand() % 9) + 1;
}


//All Rules
int isValueInColumn (int column, int value){
    for (int i = 0; i < 9; i++){
        if (value == gameField[i][column]) {
            return 1;
        }
    }
    return 0;
}

int isValueInRow (int row, int value){
    for (int i = 0; i < 9; i++){
        if (value == gameField[row][i]) {
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
                return 1;
            }
        }
    }
    return 0;
}

int checkAllRulesNoText(int row, int column, int value){
    if (isValueInRow(row,value) == 0){
        if (isValueInColumn(column,value) == 0){
            if (isValueInBox(row,column,value) == 0){
                return 1;
            }
        }
    }
    return 0;
}

//If the value is checks all rules a 1 is given back
int checkAllRules(int row, int column, int value){
    if (isValueInRow(row,value) == 0){
        if (isValueInColumn(column,value) == 0){
            if (isValueInBox(row,column,value) == 0){
                return 1;
            }
            printf("The Value %d is already in this Box!\n", value);
        }
        printf("The Value %d is already in this column!\n", value);
    }
    printf("The Value %d is already in this row!\n", value);
    return 0;
}

//Removes the Numbers of the Array and puts a 0 in there
void removeKNumbers(int nonhiddennumbers){
    int count = 81-nonhiddennumbers;
    while (count != 0)
    {
        int cellId = randomGenerator81();

        int x = cellId/9;
        int y = cellId%9;

        if (gameField[x][y] != 0)
        {
            count--;
            gameField[x][y] = 0;
        }
    }
}

//An algorithmen which fills all the remaining numbers
int fillRemaining(int x, int y){
    if (y >= 9 && x < 9 - 1)
    {
        x = x + 1;
        y = 0;
    }
    if (x >= 9 && y >= 9)
        return 1;

    if (x < 3)
    {
        if (y < 3)
            y = 3;
    }
    else if (x < 9 - 3)
    {
        if (y == (int)(x / 3) * 3)
            y = y + 3;
    }
    else
    {
        if (y == 9 - 3)
        {
            x = x + 1;
            y = 0;
            if (x >= 9)
                return 1;
        }
    }

    for (int value = 1; value<=9; value++)
    {
        if (checkAllRulesNoText(x, y, value) == 1)
        {
            gameField[x][y] = value;
            if(fillRemaining(x, y + 1) == 1){
                return 1;
            }
            gameField[x][y] = 0;
        }
    }
    return 0;
}

//Fills the Box
void fillBox(int row, int column){
    int value;
    for (int i = 0; i<3;i++){
        for (int j=0;j<3;j++){
            do {
                value = randomGenerator();
            } while (isValueInBox(row, column, value) == 1);
            gameField[row+i][column+j] = value;
        }
    }
}

//Fills the Diagonal from Top Left to Bottom Right
void fillDiagonal(){
    for (int i = 0; i < 9; i=i+3){
        fillBox(i, i);
    }
}

void generateSudoku(int nonhiddennumbers) {
    fillDiagonal();
    fillRemaining(0, 3);
    removeKNumbers(nonhiddennumbers);
}


//Fills the gameField Array with 0
void setGameField(int nonhiddennumbers) {
    generateSudoku(nonhiddennumbers);
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
            if(gameField[x][y] == 0){
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    char playerName[20];
    char column;
    srand(time(NULL));
    int nonhiddenNumbers;
    int row;
    int inputValue;

    //If incorrect input ask again
    do{
        printf("Please enter your name:");
    } while (scanf("%s", &playerName) == 0);
    getchar();

    do{
        printf("Please enter your amount of Numbers which should be shown:");
    } while (scanf("%d", &nonhiddenNumbers) == 0);
    getchar();
    setGameField(nonhiddenNumbers);

    //This will go one as long the game is not finished
    while (0 == gameEnded()) {
        system("clear");
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

    printf("Game Finished\n");
    system("pause");
    return 0;
}