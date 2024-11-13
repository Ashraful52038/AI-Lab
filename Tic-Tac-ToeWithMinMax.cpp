#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;
char ai = 'X';
char human = 'O';
vector<vector<char>> board(3, vector<char>(3, ' ')); // Initialize a 3x3 Tic-Tac-Toe board

struct Move {
    int row;
    int col;
};

int scores(char result) {
    if (result == ai) return 1;
    else if (result == human) return -1;
    else return 0;
}

char checkWinner() {
    // Rows, columns, and diagonals check
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];

    // Check if there are empty spots
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return '\0'; // Game still ongoing

    return 'T'; // Tie
}

int minimax(int depth, bool isMaximizing) {
    char result = checkWinner();
    if (result != '\0') {
        return scores(result);
    }

    if (isMaximizing) {
        int bestScore = -INF;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = ai;
                    int score = minimax(depth + 1, false);
                    board[i][j] = ' ';
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INF;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = human;
                    int score = minimax(depth + 1, true);
                    board[i][j] = ' ';
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

Move findBestMove() {
    int bestScore = -INF;
    Move bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = ai;
                int score = minimax(0, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

void printBoard() {
    cout << "Current board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << (board[i][j] == ' ' ? '.' : board[i][j]) << " ";
        }
        cout << endl;
    }
}

void playerMove() {
    int row, col;
    while (true) {
        cout << "Enter your move (row and column from 0 to 2): ";
        cin >> row >> col;
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = human;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

int main() {
    cout << "Tic-Tac-Toe Game (You are 'O' and AI is 'X')\n";
    while (true) {
        printBoard();

        // Human's turn
        playerMove();
        if (checkWinner() != '\0') break;

        // AI's turn
        Move aiMove = findBestMove();
        board[aiMove.row][aiMove.col] = ai;
        cout << "AI placed at (" << aiMove.row << ", " << aiMove.col << ")\n";
        if (checkWinner() != '\0') break;
    }

    printBoard();
    char result = checkWinner();
    if (result == human) {
        cout << "You win!\n";
    } else if (result == ai) {
        cout << "AI wins!\n";
    } else {
        cout << "It's a tie!\n";
    }

    return 0;
}
