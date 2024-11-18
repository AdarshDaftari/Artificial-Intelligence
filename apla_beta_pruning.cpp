#include <iostream>
#include <vector>
#include <string>
using namespace std;

int currentTurn = 1;
int MAX_DEPTH = 4;
long long totalCalls = 0;

struct MinimaxOutcome {
    int score;
    vector<int> moves;
};

void playerMove(vector<vector<int>> &board, int turn) {
    bool validMove = true;
    int move;
    while (validMove) {
        cout << "Enter your move (1-9): ";
        cin >> move;
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;

        if (move >= 1 && move <= 9 && (board[row][col] == 2)) {
            if (turn % 2 != 0) {
                board[row][col] = 3;  // X
            } else {
                board[row][col] = 5;  // O
            }
            validMove = false;
        } else {
            cout << "Invalid Move!" << endl;
        }
    }
}

bool hasWinner(vector<vector<int>> &board, int player) {
    int product = player * player * player;

    for (int i = 0; i < 3; i++) {
        if ((board[i][0] * board[i][1] * board[i][2]) == product) {
            return true;
        }
    }

    for (int i = 0; i < 3; i++) {
        if ((board[0][i] * board[1][i] * board[2][i]) == product) {
            return true;
        }
    }

    if ((board[0][0] * board[1][1] * board[2][2]) == product || 
        (board[0][2] * board[1][1] * board[2][0]) == product) {
        return true;
    }
    return false;
}

int findWinningMove(vector<vector<int>> &board, int player) {
    int product = player * player * 2;
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] * board[i][1] * board[i][2]) == product) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 2)
                    return i * 3 + j + 1;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if ((board[0][i] * board[1][i] * board[2][i]) == product) {
            for (int j = 0; j < 3; j++) {
                if (board[j][i] == 2)
                    return j * 3 + i + 1;
            }
        }
    }
    if ((board[0][0] * board[1][1] * board[2][2]) == product) {
        for (int i = 0; i < 3; i++) {
            if (board[i][i] == 2)
                return i * 3 + i + 1;
        }
    }
    if ((board[0][2] * board[1][1] * board[2][0]) == product) {
        for (int i = 0; i < 3; i++) {
            if (board[i][2 - i] == 2)
                return i * 3 + (2 - i) + 1;
        }
    }
    return 0;
}

int evaluateBoard(vector<vector<int>> board, int move, int player) {
    int score = 0;
    int opponent = (player == 3) ? 5 : 3; 

    if (hasWinner(board, player)) {
        score += 100; 
    } else if (hasWinner(board, opponent)) {
        score -= 100;
    } else {
        if (findWinningMove(board, player) != 0) {
            score += 50; 
        }
        if (findWinningMove(board, opponent) != 0) {
            score -= 50; 
        }

        if (move == 5) {
            score -= 10; 
        }

        if (move == 1) score -= 1; 
        if (move == 2) score -= 2;
        if (move == 3) score -= 1; 
        if (move == 4) score -= 2; 
        if (move == 5) score -= 3; 
        if (move == 6) score -= 2; 
        if (move == 7) score -= 1; 
        if (move == 8) score -= 2; 
        if (move == 9) score -= 1; 
    }

    return score;
}

void showBoard(const vector<vector<int>> &board) {
    cout << "-------------------" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 3) cout << "X  | ";
            else if (board[i][j] == 5) cout << "O  | ";
            else cout << "   | ";
        }
        cout << endl;
        cout << "-------------------" << endl;
    }
}

MinimaxOutcome minimax(vector<vector<int>> board, int player, int depth, int alpha, int beta, int movePosition) {
    totalCalls++;
    MinimaxOutcome outcome;
    outcome.score = 0;
    
    // Base case
    if (depth >= MAX_DEPTH || hasWinner(board, 3) || hasWinner(board, 5)) {
        outcome.score = evaluateBoard(board, movePosition, player);
        return outcome;
    }

    vector<int> availableMoves;
    for (int i = 1; i <= 9; i++) {
        int row = (i - 1) / 3;
        int col = (i - 1) % 3;
        if (board[row][col] == 2) {
            availableMoves.push_back(i);
        }
    }

    // No available moves
    if (availableMoves.empty()) {
        outcome.score = evaluateBoard(board, movePosition, player);
        return outcome;
    }

    int bestScore = -1000;
    vector<int> bestMoves;

    for (int move : availableMoves) {
        auto new_board = board;
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;
        new_board[row][col] = player;

        MinimaxOutcome childOutcome = minimax(new_board, (player == 3) ? 5 : 3, depth + 1, -beta, -alpha, move);
        
        int newScore = -childOutcome.score; 

        
        if (newScore > alpha) {
            alpha = newScore;
            bestMoves = childOutcome.moves;
            bestMoves.insert(bestMoves.begin(), move);
            if (alpha >= beta) {
                outcome.score = alpha;
                outcome.moves = bestMoves;
                return outcome;  // Alpha-Beta Pruning
            }
        }
    }

    outcome.score = alpha;
    outcome.moves = bestMoves;
    return outcome;
}

void aiMove(vector<vector<int>> &board, int turn) {
    totalCalls = 0;
    int player = (turn % 2 == 0) ? 5 : 3;
    
    int alpha = -1000; // Alpha
    int beta = 1000;   // Beta

    MinimaxOutcome outcome = minimax(board, player, 0, alpha, beta, 0);

    if (!outcome.moves.empty()) {
        int bestMove = outcome.moves[0];
        int row = (bestMove - 1) / 3;
        int col = (bestMove - 1) % 3;
        board[row][col] = player;
        
        cout << "Computer chose: " << bestMove << endl;
        cout << "Expected score: " << outcome.score << endl;
        cout << "Moves taken: ";
        for (int move : outcome.moves) {
            cout << move << " ";
        }
        cout << endl;
    }

    cout << "Total recursive calls: " << totalCalls << endl;
}

int main() {
    vector<vector<int>> board(3, vector<int>(3, 2));
    while (true) {
        showBoard(board);
        if (hasWinner(board, 5)) {
            cout << "Computer Wins!" << endl;
            break;
        }
        if (hasWinner(board, 3)) {
            cout << "You Win!" << endl;
            break;
        }
        if (currentTurn > 9) {
            cout << "It's a Draw!" << endl;
            break;
        }
        playerMove(board, currentTurn);
        currentTurn++;

        showBoard(board);
        if (hasWinner(board, 5)) {
            cout << "Computer Wins!" << endl;
            break;
        }
        if (hasWinner(board, 3)) {
            cout << "You Win!" << endl;
            break;
        }
        if (currentTurn > 9) {
            cout << "It's a Draw!" << endl;
            break;
        }
        aiMove(board, currentTurn);
        currentTurn++;
    }
    showBoard(board);
    return 0;
}
