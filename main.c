#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define LENGTH(array) (sizeof(array)/sizeof(array[0]))

// 0 equals false
// 1 equals true

void Draw(char playerName[]){
    int contentField[9][9];
    int displayedField[15][15];
    int i = 0;
    printf("Your name: %20s\n",playerName);

    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            if (x % (3 + 1) == 1 && y % (3 + 1) == 1) {
                displayedField[x][y] = ' ';
            } else {
                if (x % (3 + 1) == 1 && y != 0) {
                    displayedField[x][y] = '-';
                } else {
                    if (y % (3 + 1) == 1 && x != 0) {
                        displayedField[x][y] = '|';
                    } else {
                        // insert fieldValues
                        if (x != 0 && y != 0) {
                            displayedField[x][y] = contentField[(x - 2 - ((x - 2) / (3 + 1))) * 3 * 3 +
                                                                (y - 2 - ((y - 2) / (3 + 1)))];
                        } else {
                            displayedField[x][y] = ' ';
                        }

                    }
                }
            }
        }
    }

    for (int x = 0; x < 15; x++){
        for (int y = 0; y < 15; y++) {
            printf("%c", displayedField[x][y]);
        }
        printf(" \n");
    }
    return;
}

int main() {
    int gameFinished = 0;
    char playerName[20];
    printf("Please enter your name:\n");
    scanf("%20s", playerName);

    //This will go one as long as the game goes
    while (0 == gameFinished){
        Draw(playerName);
        gameFinished = 1;
    }
    printf("Game Finished");
    return 0;
}