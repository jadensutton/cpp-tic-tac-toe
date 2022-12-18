#include <iostream>
#include <vector>

using namespace std;

int checkForWinner(char board[3]) {
    bool spacesRemaining = false;

    for (int i = 0; i <= 2; i++) {
        if (board[3 * i] != '-' && board[3 * i] == board[3 * i + 1] && board[3 * i + 1] == board[3 * i + 2]) {
            return (board[3 * i] == 'x') ? 1 : -1;
        } else if (board[i] != '-' && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return (board[i] == 'x') ? 1 : -1;
        }

        if (board[3 * i] == '-' || board[3 * i + 1] == '-' || board[3 * i + 2] == '-') {
            spacesRemaining = true;
        }
    }

    if (!spacesRemaining) {
        return 0;
    }

    if (board[0] != '-' && board[0] == board[4] && board[4] == board[8]) {
        return (board[0] == 'x') ? 1 : -1;
    } else if (board[2] != '-' && board[2] == board[4] && board[4] == board[6]) {
        return (board[2] == 'x') ? 1 : -1;
    }

    return 2;
}

void printBoard(char board[9]) {
    cout << "Current board:" << endl;
    for (int i = 0; i <= 2; i++) {
        cout << board[3 * i] << ' ' << board[3 * i + 1] << ' ' << board[3 * i + 2] << endl;
    }
}

bool isValidMove(vector<int> emptySpaces, int loc) {
    if (loc < 0 || loc > 8) {
        return false;
    }

    for (int i = 0; i < emptySpaces.size(); i++) {
        if (emptySpaces[i] == loc) {
            return true;
        }
    }

    return false;
}

void findEmptySpaces(char board[9], vector<int> *emptySpaces) {
    for (int i = 0; i <= 8; i++) {
        if (board[i] == '-') {
            emptySpaces->push_back(i);
        }
    }
}

int minimax(char board[9], int *move) {
    vector<int> emptySpaces;
    findEmptySpaces(board, &emptySpaces);

    int code = checkForWinner(board);
    if (code != 2) {
        return -1 * code * (emptySpaces.size() + 1);
    }

    int max;
    for (int i = 0; i < emptySpaces.size(); i++) {
        char board_copy[9];
        for(int j = 0; j <= 8; j++) {
            board_copy[j] = board[j];
        }
        board_copy[emptySpaces[i]] = 'o';

        int utility_score = 0;
        for (int j = 0; j < emptySpaces.size(); j++) {
            if (i != j) {
                char board_copy_copy[9];
                for(int n = 0; n <= 8; n++) {
                    board_copy_copy[n] = board_copy[n];
                }
                board_copy_copy[emptySpaces[j]] = 'x';              
                utility_score += minimax(board_copy_copy, NULL);
            }
        }

        if (i == 0 || utility_score > max) {
            max = utility_score;
            if (move != NULL) {
                *move = emptySpaces[i];
            }
        }
    }
    
    return max;
}

int opponentTurn(char board[9]) {
    int move;
    minimax(board, &move);
    
    return move;
}

int main() {
    char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
    while (1)
    {
        int loc;

        bool validMove = false;
        while (!validMove) {
            cout << "Enter board coordinate (0 - 8)" << endl;
            cin >> loc;

            vector<int> emptySpaces;
            findEmptySpaces(board, &emptySpaces);
            
            validMove = isValidMove(emptySpaces, loc);

            if (!validMove) {
                cout << "Invalid move!" << endl;
            }
        }


        board[loc] = 'x';

        printBoard(board);

        int code = checkForWinner(board);
        if (code == 1) {
            cout << "You win!";
            break;
        } else if (code == -1) {
            cout << "You lose!";
            break;
        } else if (code == 0) {
            cout << "This game is a tie!";
            break;
        }

        int move = opponentTurn(board);
        board[move] = 'o';

        printBoard(board);

        code = checkForWinner(board);
        if (code == 1) {
            cout << "You win!";
            break;
        } else if (code == -1) {
            cout << "You lose!";
            break;
        } else if (code == 0) {
            cout << "This game is a tie!";
            break;
        }        
    }

    return 0;
}