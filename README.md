# NQueenSolver

## Overview

NQueenSolver is a program that solves the classic N-Queens puzzle. The objective of the puzzle is to place N queens on an N x N chessboard such that no two queens threaten each other. This means that no two queens can share the same row, column, or diagonal.

## Features

- Solves the N-Queens problem for any size N.
- Prints all possible solutions to a text file.
- Tracks and displays the number of iterations and solutions found.
- Calculates and displays the average number of iterations per solution.
- Measures and displays the total time taken to find all solutions.

## Usage

1. **Clone the Repository:**
    ```sh
    git clone https://github.com/stefanoranghetto/NQueenSolver.git
    cd NQueenSolver
    ```

2. **Compile the Program:**
    ```sh
    gcc -o NQueenSolver NQueenSolver.c -lm
    ```

3. **Run the Program:**
    ```sh
    ./NQueenSolver
    ```

    When prompted, enter the size of the board (N). If an invalid input is provided, the default size of 8 will be used.

## Output

- The program generates a text file named in the format `N_Queen_solution_YYYYMMDD_HHMMSS.txt` where `N` is the size of the board and the timestamp corresponds to when the program was run.
- The file contains:
  - The total number of solutions found.
  - The total number of iterations.
  - The average number of iterations per solution.
  - The time taken to find all solutions.
  - A detailed listing of each solution, showing the board configuration.

## Code Structure

- **main**: The entry point of the program. It handles user input, file creation, and output display.
- **solveNQ**: Initializes the board and starts the recursive solving process.
- **solve**: The recursive function that attempts to place queens on the board while tracking iterations and finding solutions.
- **printSolution**: Prints a single solution to the specified file.

## Example Output

Upon running the program and entering the size of the board as 8, you will get an output file similar to:

    ```sh
    
    Number of solutions found: 92
    Number of iterations: 205024
    Average iterations: 2228
    Time taken: 0.12 seconds
    
    Solution 1 - Iterations 2228
    Q . . . . . . .
    . . . . Q . . .
    . . . . . . Q .
    . . . Q . . . .
    . Q . . . . . .
    . . . . . Q . .
    . . Q . . . . .
    . . . . . . . Q
    
    ...

    ```

  
## Author

- Stefano Ranghetto
- [GitHub Profile](https://github.com/RangO1972)

## License

This project is licensed under the MIT License.
Feel free to customize this README file as per your requirements or any additional details you want to include.
