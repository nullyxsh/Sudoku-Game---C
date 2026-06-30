#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int ran_Num();
int check_row(int num,int column,int board[9][9]);
int check_column(int num,int row,int board[9][9]);
int check_3x3(int num,int row,int column,int board[9][9]);
int insert(int row,int column,int board[9][9]);

int ran_Num(){  
    return rand() % 9 + 1;
}
int check_row(int num,int row,int board[9][9]){
    for(int i=0;i<9;i++){
        if(num==board[row][i]){
            return 0;
        }
    }
    return 1;

}
int check_column(int num,int column,int board[9][9]){
    for(int i=0;i<9;i++){
        if(num==board[i][column]){
            return 0;
        }
    }
    return 1;
}
int check_3x3(int num, int row, int column, int board[9][9]){
    int insert_row = (row / 3) * 3;
    int insert_col = (column / 3) * 3;

    for(int i = insert_row; i < insert_row + 3; i++)
    {
        for(int j = insert_col; j < insert_col + 3; j++)
        {
            if(board[i][j] == num)
            {
                return 0;
            }
        }
    }

    return 1;
}
int possible_num(int poss[],int nums[],int row,int column,int board[9][9]){

    for(int i=0;i<9;i++){
        poss[i]=0;
    }
    int l=0;
    for(int i=0;i<9;i++){
        int n=nums[i];
        if(check_row(n,row,board) && check_column(n,column,board) && check_3x3(n,row,column,board)){
            poss[l]=nums[i];
            l++;
        }
    }
    return l;

}

int main() {
    int board[9][9] = {0};
    int empty_cell[81][2] = {0};
    int try_index[9][9] = {0};

    srand(time(NULL));
    int nums[9] = {1,2,3,4,5,6,7,8,9};
    int poss[9];

    for (int i = 0; i < 9; i++) {
        int r = rand() % 9;
        int t = nums[i]; nums[i] = nums[r]; nums[r] = t;
    }

    

    //input of unsolved sudoku [0 mark empty space]
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            scanf("%d",&board[i][j]);
        }
    }

    //print given input sudoku
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) printf("\t[%d]", board[i][j]);
    //     printf("\n\n");
    // }

    //finding empty slots
    int x=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]==0){
                empty_cell[x][0]=i;
                empty_cell[x][1]=j;
                x++;
            }
        }
    }
    int max=x;
    x=0;
    //printing empty slots
    // for (int i = 0; i < max; i++) {
    //     for (int j = 0; j < 2; j++) printf("\t[%d]", empty_cell[i][j]);
    //     printf("\n\n");
    // }


    int i = 0, j = 0;
    while (x<max) {
        int row = empty_cell[x][0];
        int col = empty_cell[x][1];
        board[row][col] = 0; 
        // board[i][j] = 0;
        int s = possible_num(poss, nums, empty_cell[x][0], empty_cell[x][1], board);

        int placed = 0;
        for (int k = try_index[empty_cell[x][0]][empty_cell[x][1]]; k < s; k++) {
            board[row][col] = poss[k];
            try_index[row][col] = k + 1;
            placed = 1;
            break;
        }

        if (!placed) {
            try_index[row][col] = 0;
            board[row][col] = 0;
            if (x == 0) {
                printf("Bhari mistake hua hai ! maybe sudoku shi generate nhi hua!");
                break;
            } else {
                x--;
            }
        } 
        else {
            x++;
        }
        
    }

    printf("Printing Solved Sudoku:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) printf("\t[%d]", board[i][j]);
        printf("\n\n");
    }

    
    return 0;
}

