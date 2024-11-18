#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum Player { NONE, WHITE, BLACK };

struct Piece {
    PieceType type;
    Player player;

    Piece() : type(EMPTY), player(NONE) {}
    Piece(PieceType t, Player p) : type(t), player(p) {}

    char getSymbol() const {
        if (player == WHITE) {
            switch (type) {
                case PAWN: return 'P';
                case ROOK: return 'R';
                case KNIGHT: return 'N';
                case BISHOP: return 'B';
                case QUEEN: return 'Q';
                case KING: return 'K';
                default: return '.';
            }
        } else if (player == BLACK) {
            switch (type) {
                case PAWN: return 'p';
                case ROOK: return 'r';
                case KNIGHT: return 'n';
                case BISHOP: return 'b';
                case QUEEN: return 'q';
                case KING: return 'k';
                default: return '.';
            }
        }
        return '.';
    }
};

class ChessBoard {
private:
    vector<vector<Piece>> board;

public:
    ChessBoard() {
        board.resize(8, vector<Piece>(8, Piece()));

        // Set up the initial board configuration
        setupBoard();
    }

    void setupBoard() {
        // Set up pawns
        for (int i = 0; i < 8; ++i) {
            board[1][i] = Piece(PAWN, BLACK);
            board[6][i] = Piece(PAWN, WHITE);
        }

        // Set up rooks
        board[0][0] = board[0][7] = Piece(ROOK, BLACK);
        board[7][0] = board[7][7] = Piece(ROOK, WHITE);

        // Set up knights
        board[0][1] = board[0][6] = Piece(KNIGHT, BLACK);
        board[7][1] = board[7][6] = Piece(KNIGHT, WHITE);

        // Set up bishops
        board[0][2] = board[0][5] = Piece(BISHOP, BLACK);
        board[7][2] = board[7][5] = Piece(BISHOP, WHITE);

        // Set up queens
        board[0][3] = Piece(QUEEN, BLACK);
        board[7][3] = Piece(QUEEN, WHITE);

        // Set up kings
        board[0][4] = Piece(KING, BLACK);
        board[7][4] = Piece(KING, WHITE);
    }

    void printBoard() {
        cout << "   a b c d e f g h\n";
        cout << "  +-----------------+\n";
        for (int i = 0; i < 8; ++i) {
            cout << 8 - i << " | ";
            for (int j = 0; j < 8; ++j) {
                cout << board[i][j].getSymbol() << " ";
            }
            cout << "| " << 8 - i << endl;
        }
        cout << "  +-----------------+\n";
        cout << "   a b c d e f g h\n";
    }

    bool isValidMove(int startX, int startY, int endX, int endY, Player player) {
        // Basic boundary check
        if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
            endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
            return false;
        }

        // Basic piece ownership check
        Piece piece = board[startX][startY];
        if (piece.player != player) {
            return false;
        }

        // Add additional rules here for each piece's movement
        // This example just allows any move for simplicity, which is not real chess logic
        return true;
    }

    bool movePiece(string move, Player player) {
        // Parse move (e.g., "e2 e4" -> from e2 to e4)
        int startY = move[0] - 'a';
        int startX = 8 - (move[1] - '0');
        int endY = move[3] - 'a';
        int endX = 8 - (move[4] - '0');

        if (!isValidMove(startX, startY, endX, endY, player)) {
            cout << "Invalid move!\n";
            return false;
        }

        // Move the piece
        board[endX][endY] = board[startX][startY];
        board[startX][startY] = Piece(); // Clear the original position
        return true;
    }
};

int main() {
    ChessBoard chessBoard;
    Player currentPlayer = WHITE;

    while (true) {
        chessBoard.printBoard();
        string move;

        if (currentPlayer == WHITE) {
            cout << "White's move: ";
        } else {
            cout << "Black's move: ";
        }

        cin >> move;

        if (chessBoard.movePiece(move, currentPlayer)) {
            currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE; // Switch turn
        } else {
            cout << "Invalid move, try again.\n";
        }
    }

    return 0;
}
