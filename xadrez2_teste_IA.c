#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

// Trabalho ja feito com I.A
// pegar Ideias e base para fazer o nosso.


// Tamanho do tabuleiro
#define ROWS 5
#define COLS 6

// Função para verificar se o caminho está bloqueado (movimento simples, sem obstáculos)
bool is_path_blocked(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    int dr = (end_row > start_row) ? 1 : (end_row < start_row) ? -1 : 0;
    int dc = (end_col > start_col) ? 1 : (end_col < start_col) ? -1 : 0;
    int r = start_row + dr, c = start_col + dc;
    while (r != end_row || c != end_col) {
        if (board[r][c] != ' ') return true;
        if (r != end_row) r += dr;
        if (c != end_col) c += dc;
    }
    return false;
}

// Função para verificar se o caractere é maiúsculo (peça do adversário)
bool is_upper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

// Função para inicializar o tabuleiro
void inicializar_tabuleiro(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            board[i][j] = ' ';
    // Exemplo de peças iniciais (ajuste conforme as regras do seu jogo)
    board[0][0] = 'x';
    board[0][1] = 'y';
    board[0][2] = 'z';
    board[4][5] = 'X';
    board[4][4] = 'Y';
    board[4][3] = 'Z';
}

// Função para exibir o tabuleiro
void exibir_tabuleiro(char board[ROWS][COLS]) {
    printf("  ");
    for (int j = 0; j < COLS; j++) printf("%d ", j);
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// --- Suas funções de movimento já estão aqui (is_valid_X_move, is_valid_Y_move, is_valid_Z_move, make_move) ---

// Copie as funções de movimento daqui para baixo...

// x
bool is_valid_X_move(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    int delta_row = abs(end_row - start_row);
    int delta_col = abs(end_col - start_col);

    if ((delta_row <= 2 && delta_col <= 2) && (delta_row > 0 || delta_col > 0)) {
        if (is_path_blocked(start_row, start_col, end_row, end_col, board)) {
            return false;
        }
        if (isupper(board[end_row][end_col]) || board[end_row][end_col] == ' ') {
            return true;
        }
        return false;
    }
    return false;
}

// y
bool is_valid_Y_move(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    int distancia = abs(end_row - start_row) + abs(end_col - start_col);

    if (distancia == 2) {
        if (is_path_blocked(start_row, start_col, end_row, end_col, board)) {
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

// z
bool is_valid_Z_move(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    if (start_row == end_row || start_col == end_col) {
        int delta_row = abs(end_row - start_row);
        int delta_col = abs(end_col - start_col);

        if ((delta_row <= 2 && delta_col <= 2) && (delta_row > 0 || delta_col > 0)) {
            if (is_path_blocked(start_row, start_col, end_row, end_col, board)) {
                return false;
            }
            return board[end_row][end_col] != 'Y';
        }
    }
    return false;
}

bool make_move(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
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

// Função principal
int main() {
    char board[ROWS][COLS];
    inicializar_tabuleiro(board);

    int start_row, start_col, end_row, end_col;
    while (1) {
        exibir_tabuleiro(board);
        printf("Digite linha e coluna de origem e destino (ou -1 para sair): ");
        scanf("%d %d %d %d", &start_row, &start_col, &end_row, &end_col);
        if (start_row == -1) break;
        if (make_move(start_row, start_col, end_row, end_col, board)) {
            printf("Movimento realizado!\n");
        } else {
            printf("Movimento inválido!\n");
        }
    }
    return 0;
}