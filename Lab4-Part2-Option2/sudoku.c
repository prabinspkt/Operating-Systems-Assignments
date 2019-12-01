#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 9

// Sudoku board. Modify this to test your checker!
// 0 == empty cell; 1-9 is the filled in digit.
// int board[SIZE][SIZE] = {
//     {1,0,0,0,0,0,0,0,0},
//     {0,2,0,0,0,0,0,0,0},
//     {0,0,3,0,0,0,0,0,0},
//     {0,0,0,4,0,0,0,0,0},
//     {0,0,0,0,5,0,0,0,0},
//     {0,0,0,0,0,6,0,0,0},
//     {0,0,0,0,0,0,7,0,0},
//     {0,0,0,0,0,0,0,8,0},
//     {0,0,0,0,0,0,0,0,9},
// };

int board[SIZE][SIZE] = {
    {9,6,3,7,1,8,2,4,5},
    {5,1,8,3,2,4,9,7,6},
    {2,4,7,6,9,5,1,3,8},
    {3,2,6,4,5,9,7,8,1},
    {7,8,4,1,6,3,5,9,2},
    {1,9,5,8,7,2,3,6,4},
    {8,7,9,2,4,1,6,5,3},
    {6,3,1,5,8,7,4,2,9},
    {4,5,2,9,3,6,8,1,7},
};

// Box index [start_row][start_col]
int box_row_col[SIZE][2] = {
	{0,0},{0,3},{0,6},
	{3,0},{3,3},{3,6},
	{6,0},{6,3},{6,6},
};

bool row_check[SIZE] = {true, true, true, true, true, true, true, true, true};
bool col_check[SIZE] = {true, true, true, true, true, true, true, true, true};
bool box_check[SIZE] = {true, true, true, true, true, true, true, true, true};

void printBoard(int board[SIZE][SIZE]) {
    for(int i = 0; i<SIZE; i++) {
        for(int j = 0; j<SIZE; j++) {
            printf("%5d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Checks the given row for duplicate numbers, and updates the row_check
// value for that row appropriately. If no number is repeated in that row,
// row_check[row] will be set to true; otherwise, it will be false.
void* checkRow(void* args) {
    int row_index = *(int*) args;
    int * row = board[row_index];
    int elements[9] = {0};
    for (int i = 0; i < 9; i++) {
        elements[row[i]-1]++;
    }
    for (int j = 0; j < 9; j++) {
        if (elements[j] != 1) {
            row_check[row_index] = false;
        }
    }
    return NULL;
}

// Checks the given col for duplicate numbers, and updates the col_check
// value for that col appropriately. If no number is repeated in that col,
// col_check[col] will be set to true; otherwise, it will be false.
void* checkCol(void* args) {
    int col_index = *(int*) args;
    int elements[9] = {0};
    for (int i = 0; i < 9; i++) {
        elements[board[i][col_index]-1]++;
    }
    for (int j = 0; j < 9; j++) {
        if (elements[j] != 1) {
            col_check[col_index] = false;
        }
    }
    return NULL;
}

// Checks the given 3x3 box for duplicate numbers, and updates the box_check
// value for that box appropriately. If no number is repeated in that box,
// box_check[box] will be set to true; otherwise, it will be false.
void* checkBox(void* args) {
	// Starting rows and columns for the box
	// Should contain starting_row and starting_column
	int box_index = *(int *) args;
	int row = box_row_col[box_index][0];
	int col = box_row_col[box_index][1];
	int elements[9] = {0};
	for (int i = row; i < row+3; i++){
		for (int j = col; j < col+3; j++){
			elements[board[i][j]-1]++;
		}
	}
	for (int k = 0; k < 9; k++) {
        if (elements[k] != 1) {
            box_check[box_index] = false;
        }
    }
    return NULL;
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() { 
    // 1. Print the board.
    printf("Board:\n");
    printBoard(board);
    
    // 2. Create pthread_t objects for our threads.
    pthread_t threads_ids[36];
    
    // 3. Create a thread for each cell of each matrix operation.
    int th_list_index = 0;
    for (int row_i = 0; row_i < 9; row_i++) {
		pthread_create(&threads_ids[th_list_index], NULL, checkRow, &row_i);
		th_list_index++;
	}
	for (int col_i = 0; col_i < 9; col_i++) {
		pthread_create(&threads_ids[th_list_index], NULL, checkCol, &col_i);
		th_list_index++;
	}
	for (int box_i = 0; box_i < 9; box_i++) {
		pthread_create(&threads_ids[th_list_index], NULL, checkBox, &box_i);
		th_list_index++;
	}
	
    // 4. Wait for all threads to finish.
    int close_th_index = 0;
	for (int t = 0; t < 36; t++) {
		pthread_join(thread_ids[close_th_index], NULL);
		th_list_index++;
	}
    
    // 5. Print the results.
    printf("Results:\n");
    bool all_rows_passed = true;
    printf("Rows:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!row_check[i]) {
            printf("Row %i did not pass\n", i);
            all_rows_passed = false;
        }
    }
    if (all_rows_passed) {
        printf("All rows passed!\n");
    }
    
    bool all_cols_passed = true;
    printf("Cols:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!col_check[i]) {
            printf("Col %i did not pass\n", i);
            all_cols_passed = false;
        }
    }
    if (all_cols_passed) {
        printf("All cols passed!\n");
    }
    
    bool all_boxes_passed = true;
    printf("Boxes:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!box_check[i]) {
            printf("Box %i did not pass\n", i);
            all_boxes_passed = false;
        }
    }
    if (all_boxes_passed) {
        printf("All boxes passed!\n");
    }
    return 0;
}
