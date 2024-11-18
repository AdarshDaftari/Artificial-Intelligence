#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

#define PLAYER 'O'
#define COMPUTER 'X'

char board[3][3] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }
};

// Function to print the board
void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "--+---+--" << endl;
    }
    cout << endl;
}

// Function to check if there are moves left on the board
bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// Function to evaluate the current state of the board
int evaluate() {
    // Check rows, columns, and diagonals for a win
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTER) return 1000;
            else if (board[row][0] == PLAYER) return -1000;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTER) return 1000;
            else if (board[0][col] == PLAYER) return -1000;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER) return 1000;
        else if (board[0][0] == PLAYER) return -1000;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER) return 1000;
        else if (board[0][2] == PLAYER) return -1000;
    }

    // Assign scores based on positions
    int score = 0;

    // Center position
    if (board[1][1] == COMPUTER) score += 10;
    else if (board[1][1] == PLAYER) score -= 10;

    // Corner positions
    int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
    for (int i = 0; i < 4; i++) {
        int x = corners[i][0];
        int y = corners[i][1];
        if (board[x][y] == COMPUTER) score += 5;
        else if (board[x][y] == PLAYER) score -= 5;
    }

    return score;
}

// Minimax function
int minimax(int depth, bool isMax) {
    int score = evaluate();

    if (score == 1000 || score == -1000)
        return score;

    if (!isMovesLeft())
        return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    best = max(best, minimax(depth + 1, !isMax));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(depth + 1, !isMax));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the computer
pair<int, int> findBestMove() {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int moveVal = minimax(0, false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    cout << "Tic-Tac-Toe Game: You are 'O' and Computer is 'X'\n";
    printBoard();

    while (isMovesLeft()) {
        int x, y;
        cout << "Enter your move (row and column): ";
        cin >> x >> y;

        if (board[x][y] == ' ') {
            board[x][y] = PLAYER;
        } else {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        if (evaluate() == -1000) {
            printBoard();
            cout << "You win!\n";
            break;
        }

        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = COMPUTER;

        printBoard();

        if (evaluate() == 1000) {
            cout << "Computer wins!\n";
            break;
        }

        if (!isMovesLeft()) {
            cout << "It's a draw!\n";
        }
    }

    return 0;
}
