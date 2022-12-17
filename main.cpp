#include <iostream>

using namespace std;

void printBoard(char board[3][3]) {
    cout << "Current board:" << endl;
    for (int i = 0; i <= 2; i++) {
        cout << board[i][0] << ' ' << board[i][1] << ' ' << board[i][2] << endl;
    }
}

bool isValidMove(char board[3][3], int x, int y) {
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        return false;
    }

    return board[x][y] == '-';
}

char checkForWinner(char board[3][3]) {
    for (int i = 0; i <= 2; i++) {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        } else if (board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    } else if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    return '-';
}

int main() {
    bool gameOver = false;
    char board[3][3] = {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}};
    while (!gameOver)
    {
        int x = -1;
        int y = -1;

        bool validMove = false;
        while (!validMove) {
            cout << "Enter x coordinate (0 - 2)" << endl;
            cin >> x;

            cout << "Enter y coordinate (0 - 2)" << endl;
            cin >> y;
            
            validMove = isValidMove(board, x, y);

            if (!validMove) {
                cout << "Invalid move!" << endl;
            }
        }


        board[y][x] = 'x';

        printBoard(board);

        char winner = checkForWinner(board);
        if (winner != '-') {
            cout << winner << " wins!" << endl;
            gameOver = true;
        }
    }

    return 0;
}