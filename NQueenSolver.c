#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

// Author: Stefano Ranghetto
// GitHub: https://github.com/stefanoranghetto

long long int totalIterationCount = 0; // Total iteration counter
long long int totalIterationsSum = 0;   // Total iterations sum to calculate the average
time_t last_print_time; // Last time the solutions count was printed

int solutionCount = 0;  // Counter for the solutions found

void printSolution(int **board, int N, FILE *file) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%s ", board[i][j] ? "Q" : ".");
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
}

void solve(int **board, int row, int rowmask, int ldmask, int rdmask, int N, FILE *file) {
    totalIterationsSum++;
    totalIterationCount++;
    int all_rows_filled = (1 << N) - 1;

    // If rowmask has all bits set, it means queens have been placed successfully in all rows and the board is displayed
    if (rowmask == all_rows_filled) {
        solutionCount++;
        fprintf(file, "Solution %d - Iterations %lld\n", solutionCount, totalIterationsSum);
        totalIterationsSum = 0; // Reset for the next solution
        printSolution(board, N, file);
        time_t current_time = time(NULL);
        return;
    }

    // Extract a bit mask (safe) by rowmask, ldmask, and rdmask. All set bits of 'safe' indicate the safe column index for queen placement of this iteration for row index (row).
    int safe = all_rows_filled & (~(rowmask | ldmask | rdmask));
    while (safe) {
        // Extract the right-most set bit (safe column index) where the queen can be placed for this row
        int p = safe & (-safe);
        int col = __builtin_ctz(p);
        board[row][col] = 1;

        // Update rowmask, ldmask, and rdmask for the next row
        solve(board, row + 1, rowmask | p, (ldmask | p) << 1, (rdmask | p) >> 1, N, file);
        
        // Reset right-most set bit to 0 so, the next iteration will continue by placing the queen at another safe column index of this row
        safe = safe & (safe - 1);

        // Backtracking, replace '1' with '0'
        board[row][col] = 0;
    }
    return;
}

void solveNQ(int N, FILE *file) {
    int **board = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        board[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    int row = 0;    
    int rowmask = 0;
    int ldmask = 0;
    int rdmask = 0;

    solve(board, row, rowmask, ldmask, rdmask, N, file);

    for (int i = 0; i < N; i++) {
        free(board[i]);
    }
    free(board);
}

int main() {
    printf("NQueenSolver - Copyright 2024 Stefano Ranghetto\n");
    printf("This program solves the N-Queens puzzle, where the goal is to place N queens on an N x N chessboard so that no two queens threaten each other.\n");
    printf("Enter the size of the board (default 8): ");
    
    int N;
    if (scanf("%d", &N) != 1) {
        N = 8; // If input is not valid, use the default size 8
    }

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    char datetime[64];
    strftime(datetime, sizeof(datetime), "%Y%m%d_%H%M%S", local);

    char filename[256];
    snprintf(filename, sizeof(filename), "%d_Queen_solution_%s.txt", N, datetime);

    char tempFilename[] = "temp_queen_solutions.txt";

    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        return 1;
    }

    clock_t start = clock();

    solveNQ(N, tempFile);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    fclose(tempFile);

    FILE *finalFile = fopen(filename, "w");
    if (finalFile == NULL) {
        printf("Error opening final file!\n");
        return 1;
    }

    long long int averageIterations = totalIterationCount / solutionCount; // Calculate the average iterations

    fprintf(finalFile, "Number of solutions found: %d\n", solutionCount);
    fprintf(finalFile, "Number of iterations: %lld\n", totalIterationCount);
    fprintf(finalFile, "Average iterations: %lld\n", averageIterations);
    fprintf(finalFile, "Time taken: %.2f seconds\n", time_spent);
    fprintf(finalFile, "\n\n\n\n\n");
    
    tempFile = fopen(tempFilename, "r");
    if (tempFile == NULL) {
        printf("Error opening temporary file for reading!\n");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), tempFile)) {
        fputs(buffer, finalFile);
    }

    fclose(tempFile);
    fclose(finalFile);

    remove(tempFilename);

    printf("\nNumber of solutions found: %d\n", solutionCount);
    printf("Number of iterations: %lld\n", totalIterationCount);
    printf("Average iterations: %lld\n", averageIterations);
    printf("Time taken: %.2f seconds\n", time_spent);
    printf("Solutions saved in file %s\n", filename);
    return 0;
}
