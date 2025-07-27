#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

struct Move {
    int row, col, score = 0;
};

class TicTacToe {
public:
    TicTacToe() {
        board = vector<vector<char>>(3, vector<char>(3, EMPTY));
    }

    void play() {
        cout << "Welcome to Tic-Tac-Toe\nYou are 'X' and AI is 'O'. Let's start \n\n";
        while (true) {
            printBoard();
            playerMove();
            if (checkWin(PLAYER)) {
                printBoard();
                cout << "You win GG\n";
                break;
            }
            if (isBoardFull()) {
                printBoard();
                cout << "It's a draw! Well played \n";
                break;
            }

            cout << "AI is thinking...\n";
            aiMove();
            if (checkWin(AI)) {
                printBoard();
                cout << "AI wins Better luck next time.\n";
                break;
            }
            if (isBoardFull()) {
                printBoard();
                cout << "It's a draw! Well played!\n";
                break;
            }
        }
    }

private:
    vector<vector<char>> board;

    void printBoard() {
        cout << "\n   0   1   2\n";
        for (int i = 0; i < 3; ++i) {
            cout << i << " ";
            for (int j = 0; j < 3; ++j) {
                cout << " " << board[i][j];
                if (j < 2) cout << " |";
            }
            cout << "\n";
            if (i < 2) cout << "  ---+---+---\n";
        }
        cout << endl;
    }

    void playerMove() {
        int row, col;
        while (true) {
            cout << "Your move, Enter row and column (0, 1, or 2): ";
            cin >> row >> col;
            if (cin.fail() || row < 0 || row > 2 || col < 0 || col > 2) {
                cout << "Invalid input. Please enter numbers between 0 and 2.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (board[row][col] == EMPTY) {
                board[row][col] = PLAYER;
                break;
            } else {
                cout << "That cell is already taken. Try again.\n";
            }
        }
    }

    void aiMove() {
        Move bestMove = minimax(0, AI);
        board[bestMove.row][bestMove.col] = AI;
    }

    Move minimax(int depth, char currentPlayer) {
        if (checkWin(AI)) return { -1, -1, 10 - depth };
        if (checkWin(PLAYER)) return { -1, -1, depth - 10 };
        if (isBoardFull()) return { -1, -1, 0 };

        Move bestMove;
        bestMove.score = (currentPlayer == AI) ? numeric_limits<int>::min() : numeric_limits<int>::max();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = currentPlayer;
                    Move currentMove = minimax(depth + 1, (currentPlayer == AI) ? PLAYER : AI);
                    board[i][j] = EMPTY;
                    currentMove.row = i;
                    currentMove.col = j;

                    if (currentPlayer == AI) {
                        if (currentMove.score > bestMove.score) {
                            bestMove = currentMove;
                        }
                    } else {
                        if (currentMove.score < bestMove.score) {
                            bestMove = currentMove;
                        }
                    }
                }
            }
        }
        return bestMove;
    }

    bool checkWin(char player) {
        for (int i = 0; i < 3; ++i) {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                return true;
            }
        }
        return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
               (board[0][2] == player && board[1][1] == player && board[2][0] == player);
    }

    bool isBoardFull() {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == EMPTY) return false;
            }
        }
        return true;
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}