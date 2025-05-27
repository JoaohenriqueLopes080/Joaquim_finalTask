#include<stdio.h>
#include<stdbool.h>

// Nosso Codigo Ate Agora

int main() {

}











// fazer por ordem 
// x
bool is_valid_X_move(int start_row, int start_col, int end_row, int end_col, char board[5][6]) {
    int delta_row = abs(end_row - start_row);
    int delta_col = abs(end_col - start_col);

    if ((delta_row <= 2 && delta_col <= 2) && (delta_row > 0 || delta_col > 0)) {
        if (is_path_blocked(start_row, start_col, end_row, end_col)) {
            return false;
        }
        if (isupper(board[end_row][end_col]) || board[end_row][end_col] == ' ') {
            return true;
        }
        return false;
    }
    return false;
}

// Y
bool is_valid_Y_move(int start_row, int start_col, int end_row, int end_col, char board[5][6]) {
    int distancia = abs(end_row - start_row) + abs(end_col - start_col);

    if (distancia == 2) {
        if (is_path_blocked(start_row, start_col, end_row, end_col)) {
            return false;
        } else {
            if (is_upper(board[end_row][end_col]) || board[end_row][end_col] == ' ') {
                return true;
            } else {
                return false;
            }
        }
    } 
        return false;
}

// Z

bool is_valid_Z_move(int start_row, int start_col, int end_row, int end_col, char board[5][6]) {

    if (start_row == end_row || start_col == end_col) {
        int delta_row = abs(end_row - start_row);
        int delta_col = abs(end_col - start_col);

        if ((delta_row <= 2 && delta_col <= 2) && (delta_row > 0 || delta_col > 0)) {
            if (is_path_blocked(start_row, start_col, end_row, end_col)) {
                return false;
            }
            return board[end_row][end_col] != 'Y';
        }
    }
    return false;
}


bool make_move(int start_row, int start_col, int end_row, int end_col, char board[5][6]) {
    char peca = board[start_row][start_col];
    bool valido = false;

    if (peca == 'x') {
        valido = is_valid_X_move(start_row, start_col, end_row, end_col, board);
    } else if (peca == 'y') {
        valido = is_valid_Y_move(start_row, start_col, end_row, end_col, board);
    } else if (peca == 'z') {
        valido = is_valid_Z_move(start_row, start_col, end_row, end_col, board);
    } else {
        return false; // Peça inválida
    }

    if (valido) {
        board[end_row][end_col] = peca;
        board[start_row][start_col] = ' ';
        return true;
    } else {
        return false;
    }
}







