#include <iostream>
#include <vector>
#include <algorithm>  // For std::random_shuffle
#include <cstdlib>    // For srand, rand
#include <ctime>      // For time (to seed random number generator)
using namespace std;

// The Tic-Tac-Toe board (tracking moves with 'X' and 'O')
char board[3][3] = { {'1', '2', '3'},
                     {'4', '5', '6'},
                     {'7', '8', '9'} };

// Function to print the current board
void printBoard() {
    cout << "Current Board: \n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to print the magic square (for debugging)
void printMagicSquare(int magicSquare[3][3]) {
    cout << "Magic Square: \n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << magicSquare[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to generate a 3x3 magic square
void generateRandomMagicSquare(int magicSquare[3][3]) {
    // A valid 3x3 magic square template
    vector<int> baseMagicSquare = {8, 1, 6, 3, 5, 7, 4, 9, 2};

    // Shuffle to randomize the square
    srand(time(0));  // Seed random number generator
    random_shuffle(baseMagicSquare.begin(), baseMagicSquare.end());

    // Fill the 3x3 matrix with the shuffled magic square
    int index = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            magicSquare[i][j] = baseMagicSquare[index++];
        }
    }
}

// Function to get the value from the magic square corresponding to the move
int getMagicSquareValue(int row, int col, int magicSquare[3][3]) {
    return magicSquare[row][col];
}

// Check win using magic square logic
bool checkWinMagicSquare(char player, int magicSquare[3][3]) {
    // Collect the magic square numbers used by the player
    vector<int> playerNumbers;

    // Iterate over the board to gather the player's numbers
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == player) {
                playerNumbers.push_back(getMagicSquareValue(i, j, magicSquare));
            }
        }
    }

    // Check all possible sums of three numbers (from player's moves)
    // If any sum is 15, the player wins
    int size = playerNumbers.size();
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            for (int k = j + 1; k < size; k++) {
                if (playerNumbers[i] + playerNumbers[j] + playerNumbers[k] == 15) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Check if player can win in the next move (Posswin function)
bool posswin(char player, int magicSquare[3][3]) {
    vector<int> playerNumbers;
    vector<int> emptyNumbers;

    // Collect the magic square numbers for the player and empty cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == player) {
                playerNumbers.push_back(getMagicSquareValue(i, j, magicSquare));
            }
            else if (board[i][j] != 'X' && board[i][j] != 'O') {
                emptyNumbers.push_back(getMagicSquareValue(i, j, magicSquare));
            }
        }
    }

    // Check if there are any two numbers that sum with an empty spot to 15
    for (int i = 0; i < playerNumbers.size(); i++) {
        for (int j = i + 1; j < playerNumbers.size(); j++) {
            for (int k = 0; k < emptyNumbers.size(); k++) {
                if (playerNumbers[i] + playerNumbers[j] + emptyNumbers[k] == 15) {
                    return true;  // Player can win in the next move
                }
            }
        }
    }

    return false;
}

// Function for the computer's move (O)
void computerMove(int magicSquare[3][3]) {
    // Check if the computer can win in the next move
    if (posswin('O', magicSquare)) {
        cout << "Computer is in a winning position!" << endl;
    }

    // Basic implementation of a move (just picks the first available spot)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                board[i][j] = 'O';
                return;
            }
        }
    }
}

// Function for the player's move (X)
void playerMove() {
    int choice;
    cout << "Enter the position (1-9) where you want to place X: ";
    cin >> choice;
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = 'X';
    } else {
        cout << "Invalid move, try again.\n";
        playerMove();
    }
}

int main() {
    int magicSquare[3][3];  // Variable to store the randomized magic square
    generateRandomMagicSquare(magicSquare);  // Generate a random magic square
    printMagicSquare(magicSquare);  // Print it for debugging

    printBoard();
    while (true) {
        // Player move
        playerMove();
        printBoard();
        if (checkWinMagicSquare('X', magicSquare)) {
            cout << "Player wins!\n";
            break;
        }
        if (posswin('X', magicSquare)) {
            cout << "Player is in a winning position!" << endl;
        }

        // Computer move
        computerMove(magicSquare);
        printBoard();
        if (checkWinMagicSquare('O', magicSquare)) {
            cout << "Computer wins!\n";
            break;
        }
    } 
    return 0;
}
