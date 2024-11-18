#include <iostream>
#include <vector>
#include <climits>

const int MAX_DEPTH = 9;
int minimaxCalls = 0;
int minimaxAlphaBetaCalls = 0;

// Helper function to print the board
void printBoard(const std::vector<char>& board) {
    for (int i = 0; i < 9; i++) {
        std::cout << board[i] << ((i % 3 == 2) ? "\n" : " | ");
    }
}

// Function to check if there is a winner or if the board is full (draw)
int evaluateBoard(const std::vector<char>& board) {
    const int winCases[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (auto& win : winCases) {
        if (board[win[0]] == board[win[1]] && board[win[1]] == board[win[2]]) {
            if (board[win[0]] == 'X') return 10;
            if (board[win[0]] == 'O') return -10;
        }
    }
    return 0; // No winner
}

// Check if there are any moves left
bool movesLeft(const std::vector<char>& board) {
    for (char cell : board) {
        if (cell == '_') return true;
    }
    return false;
}

// Minimax without Alpha-Beta Pruning
int minimax(std::vector<char>& board, int depth, bool isMaximizingPlayer) {
    minimaxCalls++;
    int score = evaluateBoard(board);

    // If game is won or depth is reached
    if (score == 10 || score == -10 || depth == 0 || !movesLeft(board)) return score;

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '_') {
                board[i] = 'X';
                maxEval = std::max(maxEval, minimax(board, depth - 1, false));
                board[i] = '_';
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '_') {
                board[i] = 'O';
                minEval = std::min(minEval, minimax(board, depth - 1, true));
                board[i] = '_';
            }
        }
        return minEval;
    }
}

// Minimax with Alpha-Beta Pruning
int minimaxAlphaBeta(std::vector<char>& board, int depth, int alpha, int beta, bool isMaximizingPlayer) {
    minimaxAlphaBetaCalls++;
    int score = evaluateBoard(board);

    // If game is won or depth is reached
    if (score == 10 || score == -10 || depth == 0 || !movesLeft(board)) return score;

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '_') {
                board[i] = 'X';
                maxEval = std::max(maxEval, minimaxAlphaBeta(board, depth - 1, alpha, beta, false));
                alpha = std::max(alpha, maxEval);
                board[i] = '_';
                if (beta <= alpha) break; // Beta cutoff
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '_') {
                board[i] = 'O';
                minEval = std::min(minEval, minimaxAlphaBeta(board, depth - 1, alpha, beta, true));
                beta = std::min(beta, minEval);
                board[i] = '_';
                if (beta <= alpha) break; // Alpha cutoff
            }
        }
        return minEval;
    }
}

int main() {
    std::vector<char> board = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};

    // Run minimax without Alpha-Beta Pruning
    minimaxCalls = 0;
    int result = minimax(board, MAX_DEPTH, true);
    std::cout << "Minimax calls without Alpha-Beta Pruning: " << minimaxCalls << std::endl;

    // Run minimax with Alpha-Beta Pruning
    minimaxAlphaBetaCalls = 0;
    int resultAlphaBeta = minimaxAlphaBeta(board, MAX_DEPTH, INT_MIN, INT_MAX, true);
    std::cout << "Minimax calls with Alpha-Beta Pruning: " << minimaxAlphaBetaCalls << std::endl;

    // Compare results
    std::cout << "\nNumber of calls comparison:\n";
    std::cout << "Without Alpha-Beta Pruning: " << minimaxCalls << " calls\n";
    std::cout << "With Alpha-Beta Pruning: " << minimaxAlphaBetaCalls << " calls\n";

    return 0;
}
