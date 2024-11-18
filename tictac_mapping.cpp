#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> play_board(10, 2); // 2 indicates empty
int human = 5; // human marker
int AI = 3;    // AI marker
bool humanTurn = true; // track whose turn it is

map<int, char> mapping = {{2, '-'}, {5, 'X'}, {3, 'O'}}; // map values to symbols

// Function to display the current board
void DisplayBoard() {
    cout << "Current Board:" << endl;
    for (int i = 1; i < 10; i++) {
        cout << mapping[play_board[i]];
        if (i % 3 == 0) {
            cout << endl;
        } else {
            cout << " | ";
        }
    }
}

// Check for possible winning moves
int posswin(int p) {
    int product = p * p * 2; // Calculate product for checking winning conditions

    // Check rows
    for (int i = 1; i <= 7; i += 3) {
        int rows_product = play_board[i] * play_board[i + 1] * play_board[i + 2];
        if (rows_product == product) {
            if (play_board[i] == 2) return i;
            if (play_board[i + 1] == 2) return i + 1;
            if (play_board[i + 2] == 2) return i + 2;
        }
    }

    // Check columns
    for (int i = 1; i <= 3; ++i) {
        int cols_product = play_board[i] * play_board[i + 3] * play_board[i + 6];
        if (cols_product == product) {
            if (play_board[i] == 2) return i;
            if (play_board[i + 3] == 2) return i + 3;
            if (play_board[i + 6] == 2) return i + 6;
        }
    }

    // Check diagonals
    int diagonal_product = play_board[1] * play_board[5] * play_board[9];
    if (diagonal_product == product) {
        if (play_board[1] == 2) return 1;
        if (play_board[5] == 2) return 5;
        if (play_board[9] == 2) return 9;
    }

    diagonal_product = play_board[3] * play_board[5] * play_board[7];
    if (diagonal_product == product) {
        if (play_board[3] == 2) return 3;
        if (play_board[5] == 2) return 5;
        if (play_board[7] == 2) return 7;
    }

    return 0; // No winning move found
}

// Make a move on the board
void Go(int n) {
    if (n < 1 || n > 9 || play_board[n] != 2) {
        cout << "Invalid move: " << n << endl;
        return;
    }
    play_board[n] = humanTurn ? human : AI; // Update board with player's move
    humanTurn = !humanTurn; // Switch turn
}

// AI's move logic
void AI_Moves() {
    int move;
    // Win
    if (posswin(AI) != 0)
        move = posswin(AI);
    // Block
    else if (posswin(human) != 0)
        move = posswin(human);
    // Choose center if available
    else if (play_board[5] == 2)
        move = 5;
    // Choose first available position
    else {
        for (int i = 1; i <= 9; i++) {
            if (play_board[i] == 2) {
                move = i;
                break;
            }
        }
    }

    Go(move); // Make the move
    cout << "Computer chose: " << move << endl;
}

// Check if the board is full
bool is_playboard_full() {
    for (int i = 1; i < play_board.size(); i++)
        if (play_board[i] == 2) return false;
    return true;
}

// Check if a player has won
bool check_winner(int symbol) {
    vector<vector<int>> winningCombos = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    };

    for (const auto& combo : winningCombos)
        if (play_board[combo[0]] == symbol && play_board[combo[1]] == symbol && play_board[combo[2]] == symbol)
            return true;

    return false;
}

// Main function
int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;

    while (true) {
        DisplayBoard(); 

        if (humanTurn) {
            // Human's turn
            cout << "Your move (1-9): ";
            int move;
            cin >> move;
            if (play_board[move] == 2) {
                Go(move);
            } else {
                cout << "Invalid move! Try again." << endl;
                continue;
            }
        } else {
            // AI's turn
            cout << "Computer's Turn..." << endl;
            AI_Moves();
        }

        // Check for a winner
        if (check_winner(human)) {
            DisplayBoard();
            cout << "Congratulations! You win!" << endl;
            break;
        }
        if (check_winner(AI)) {
            DisplayBoard();
            cout << "AI wins! Better luck next time." << endl;
            break;
        }
        if (is_playboard_full()) {
            DisplayBoard();
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}
