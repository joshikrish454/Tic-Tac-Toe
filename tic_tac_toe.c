#include <stdio.h>
#include <stdbool.h>

// Function to Print Game Board
void print_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("\n");
        for (int j = 0; j < 3; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|");
    }
    printf("\n");
}

// Function to Check Winner
bool three_in_row(char board[3][3]) {
        // This Portion Checks for Column
    for (int j = 0; j < 3; j++) {
        if (
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j] &&
            (board[0][j] == 'X' || board[0][j] == 'O')
        ) {
            printf("\n%c Wins\n", board[0][j]);
            return false;
        }
    }
    // This Portion Checks for Row
    for (int i = 0; i < 3; i++) {
        if (
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            (board[i][0] == 'X' || board[i][0] == 'O')
        ) {
            printf("\n%c Wins\n", board[i][0]);
            return false;
        }
    }

    // Main Diagonal
    if (
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        (board[0][0] == 'X' || board[0][0] == 'O')
    ) {
        printf("\n%c Wins\n", board[0][0]);
        return false;
    }

    // Anti-Diagonal
    if (
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        (board[0][2] == 'X' || board[0][2] == 'O')
    ) {
        printf("\n%c Wins\n", board[0][2]);
        return false;
    }

    return true;  // No Winner yet
}

// Function to check for Tie
bool is_tie(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;  // Still Empty spots
            }
        }
    }
    return true;  // Board Full (so no tie)
}

int main(void) {

    char board[3][3] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'}
    };

    print_board(board);

    bool game_status = true;
    int new_position;
    char current_player = 'X';

    do {
        printf("\nPlayer %c, Choose a position (1 - 9): ", current_player);

        if (scanf("%d", &new_position) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // clear invalid input
            continue;
        }

        // Input Range Check (out of bound message)
        if (new_position < 1 || new_position > 9) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        // Map Position To Row & Column
        int row = (new_position - 1) / 3;
        int col = (new_position - 1) % 3;

        // Overwrite Check
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Spot already taken. Choose another.\n");
            continue;
        }

        // Place Move
        board[row][col] = current_player;

        print_board(board);

        // Check Win
        game_status = three_in_row(board);

        // Check Tie
        if (game_status && is_tie(board)) {
            printf("\nIt's a tie!\n");
            break;
        }

        // Switch Player (only if game continues)
        current_player = (current_player == 'X') ? 'O' : 'X';

    } while (game_status);

    return 0;
}
