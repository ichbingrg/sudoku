#include <stdio.h>
#include <stdbool.h>


const int matrix[9][9]= {
            {4,1,0,0,6,5,0,0,7},
            {0,0,6,0,0,7,4,8,0},
            {2,0,7,4,9,0,0,0,6},
            {0,6,0,0,7,0,1,0,0},
            {3,0,1,5,0,0,0,7,2},
            {0,9,0,0,4,2,3,0,8},
            {1,0,8,6,0,0,0,2,9},
            {0,2,0,0,1,8,6,4,0},
            {6,0,0,3,0,0,0,1,0},
            };

int sudoku[9][9]= {
            {4,1,0,0,6,5,0,0,7},
            {0,0,6,0,0,7,4,8,0},
            {2,0,7,4,9,0,0,0,6},
            {0,6,0,0,7,0,1,0,0},
            {3,0,1,5,0,0,0,7,2},
            {0,9,0,0,4,2,3,0,8},
            {1,0,8,6,0,0,0,2,9},
            {0,2,0,0,1,8,6,4,0},
            {6,0,0,3,0,0,0,1,0},
            };

void printSudoku(){
    printf("   1 2 3   4 5 6   7 8 9  \n");
    printf(" +-------+-------+-------+\n");

    for(int row = 0; row < 9 ; row++){
        printf("%d| ",row+1);

        for(int column = 0; column < 9 ; column++){
            if(sudoku[row][column] != 0)
                printf("%d ", sudoku[row][column]);
            else
                printf("  ");

            if((column+1)%3 == 0)
                printf("| ");
        }
        printf("\n");
        if((row+1)%3 == 0)
            printf(" +-------+-------+-------+\n");
    }
}

bool checkRow(int row, int column, int value, int flag){
    for (int i = 0 ; i < 9 ; i++){
        if (sudoku[row-1][i] == value){
            if (flag)
                printf("\n------------------------------------------------------->> SAMER ROW  <<<<< \n\n");
            return false;
        }
    }
    return true;
}

bool checkColumn(int row, int column, int value, int flag){
    for (int i = 0 ; i < 9 ; i++){
        if (sudoku[i][column-1] == value){
            if (flag)
                printf("\n------------------------------------------------------->> SAME COLUMN  <<<<<\n\n");
            return false;
        }
    }
    return true;
}

bool checkBox(int row, int column, int value, int flag){
    int start_row =row - ((row-1)%3) -1;  // 5 - (1)-1 = 3
    int start_column = column-((column-1)%3)-1;

    for(int i = 0; i <3; i++){
        for(int j = 0; j < 3 ; j++){
                if(sudoku[start_row+i][start_column+j] == value){
                    if (flag)
                        printf("\n---------------------------------------------->> SAME BOX <<<<< \n\n");
                    return false;
                }
        }
    }
    return true;
}

bool isEditable(int row,int column, int flag){
    if (matrix[row-1][column-1]!=0){
        if (flag)
            printf("\n---------------------------------------------->>>>> NOT EDITABLE <<<<< \n\n");
        return false;
    }
    return true;
}

bool isOkay(int row, int column, int value, int flag ){
    if ((isEditable(row,column,flag))&&(checkRow(row,column,value,flag))&&(checkColumn(row,column,value,flag))&&(checkBox(row,column,value,flag)))
        return true;
    else
        return false;

}

void fillSpace(int row,int column,int value, int flag){
    if (isOkay(row,column,value,flag))
        sudoku[row-1][column-1] = value;

}

bool isFull(){
    for (int row = 0; row < 9 ; row++){
        for(int column = 0; column < 9 ; column++){
            if(sudoku[row-1][column-1]==0)
                return false;
        }
    }
    return true;

}
void reset(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9 ; j++){
            sudoku[i][j] = matrix[i][j];
        }
    }
}
void reset_value(int row, int column){
    if (isEditable(row,column,1))
        sudoku[row-1][column-1] = 0;
}

int solve(){
//Let's solve this now
    unsigned int x = 10;
    unsigned int y = 10;
    bool a = true, b = true;
    for (int i = 0; i < 9; i++){
        for (int ii = 0; ii <9 ; ii++){
            if (sudoku[i][ii]==0){
                x = i;
                y = ii;
            }
        }
    }

    if ((x == 10)||(y==10)){
        if (isFull())
            return 1;
        return 0;
    }

    printf("Row = %d and column = %d\n", x,y);

    for (int in_val = 1; in_val < 10 ; in_val ++){
            fillSpace(x+1,y+1,in_val,0);
            if (isFull() && solve()){
                return 1;
        }else{
        fillSpace(x+1,y+1,0,0);
        }
    }
    return 0;
}


int main()
{   //check if the table is complete instead of true
    while(!isFull()) {
        printSudoku();

        int row, column , value;
        printf("\nEnter the row no(0 to quit game, 10 to reset table, 11 to auto-solve) : ");
        scanf("%d",&row);
        if(row == 0){
            printf("\n\n----------------------------You quit the game!!---------------------------------\n\n");
            return 0;
        }else if (row == 10){
            reset();
            printf("\n\n--------------------------The table has been reset------------------------------\n\n");
            continue;
        }else if (row == 11){
            if(solve()){
                printSudoku();

                printf("\n\n--------------------------The table has been solved------------------------------\n\n");}
            else{
                printf("\n\n---------------------------UNSOLVABLE---------------------------------------------\n\n");
            }
            return 0;
        }
        printf("Enter the column no: ");
        scanf("%d",&column);
        printf("Enter the number(0 to delete the existing value) :");
        scanf("%d",&value);
        if(value == 0){
            reset_value(row,column);
            printf("\n\n----------------------------The place has been reset--------------------------\n\n");
            continue;
        }

        if((value>9||value<1)||(row>9||row<1)||(column>9||column<1)){
            printf("------------------------------------Invalid-------------------------------------------- \n");
            return 0;
        }

        fillSpace(row, column, value,1);

        printf("\n\n------------------------------------------------------------------------------------\n\n");
    }

    printf("Congratulations you have completed the Sudoku\n");

    return 0;
}
