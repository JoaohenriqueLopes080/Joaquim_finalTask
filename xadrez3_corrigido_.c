#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

#define ROWS 5
#define COLS 6

int jogador_atual = 0; 

bool is_path_blocked(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    int dr = (end_row > start_row) ? 1 : (end_row < start_row) ? -1 : 0;
    int dc = (end_col > start_col) ? 1 : (end_col < start_col) ? -1 : 0;
    int r = start_row + dr, c = start_col + dc;
  
    while (r != end_row || c != end_col) {
        if (board[r][c] != ' ') 
            return true;
        if (r != end_row) r += dr;
        if (c != end_col) c += dc;
    }
    return false;
}

bool is_upper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

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

bool is_valid_Y_move(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    int delta_row = abs(end_row - start_row);
    int delta_col = abs(end_col - start_col);

    if ((delta_row == 2 && delta_col == 0) || (delta_row == 0 && delta_col == 2)) {
        if (is_path_blocked(start_row, start_col, end_row, end_col, board)) {
            return false;
        }
        if (is_upper(board[end_row][end_col]) || board[end_row][end_col] == ' ') {
            return true;
        }
    } 
    return false;
}

bool is_valid_Z_move(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    if (start_row == end_row || start_col == end_col) {
        int delta_row = abs(end_row - start_row);
        int delta_col = abs(end_col - start_col);

        if ((delta_row <= 2 && delta_col <= 2) && (delta_row > 0 || delta_col > 0)) {
            if (is_path_blocked(start_row, start_col, end_row, end_col, board)) {
                return false;
            }
            if (board[end_row][end_col] == ' ' || (is_upper(board[end_row][end_col]) && board[end_row][end_col] != 'Y')) {
                return true;
            }
        }
    }
    return false;
}

bool make_move(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    char peca = board[start_row][start_col];
    bool valido = false;

    if (tolower(peca) == 'x') {
        valido = is_valid_X_move(start_row, start_col, end_row, end_col, board);
    } else if (tolower(peca) == 'y') {
        valido = is_valid_Y_move(start_row, start_col, end_row, end_col, board);
    } else if (tolower(peca) == 'z') {
        valido = is_valid_Z_move(start_row, start_col, end_row, end_col, board);
    } else {
        return false;
    }

    if (valido) {
        board[end_row][end_col] = peca;
        board[start_row][start_col] = ' ';
        return true;
    }
    return false;
}

bool pertence_ao_jogador(char peca) {
    return (jogador_atual == 0 && islower(peca)) || 
           (jogador_atual == 1 && isupper(peca));
}

void alternar_jogador() {
    jogador_atual = !jogador_atual;
}

void mostrar_turno() {
    printf("\n--- Vez do Jogador %s ---\n", 
          jogador_atual == 0 ? "Minúsculas (x,y,z)" : "Maiúsculas (X,Y,Z)");
}

bool movimento_permitido(int start_row, int start_col, int end_row, int end_col, char board[ROWS][COLS]) {
    if (!pertence_ao_jogador(board[start_row][start_col])) {
        printf("Erro: Essa peca nao e sua!\n");
        return false;
    }
    
    if (start_row < 0 || start_row >= ROWS || start_col < 0 || start_col >= COLS ||
        end_row < 0 || end_row >= ROWS || end_col < 0 || end_col >= COLS) {
        printf("Erro: Posicao invalida!\n");
        return false;
    }
    
    return make_move(start_row, start_col, end_row, end_col, board);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    char tabuleiro[ROWS][COLS] = {
        {' ', ' ', 'Z', ' ', 'Y', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', 'x', 'y', ' ', 'z', 'X'},
        {' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' '}
    };

    int start_row, start_col, end_row, end_col;
    
    printf("=== Jogo de Estrategia ===\n");
    printf("Regras:\nPeça X: Move em diagonal ate 2 casas, sem pular peças\n");
    printf("Peça Y: Move exatamente 2 casas (horizontal/vertical), ignorando obstáculos\n");
    printf("Peça Z: Move horizontal/vertical até 2 casas, mas não captura Y\n");    
    printf("-Jogador 1: peças minúsculas (x,y,z)\n- Jogador 2: peças maiúsculas (X,Y,Z)\n");

    while (1) {
        printf("\n  ");
        for (int j = 0; j < COLS; j++) printf("%d ", j);
        printf("\n");
        for (int i = 0; i < ROWS; i++) {
            printf("%d ", i);
            for (int j = 0; j < COLS; j++) {
                printf("%c ", tabuleiro[i][j]);
            }
            printf("\n");
        }

        mostrar_turno();
        printf("Digite (linha coluna) de origem e destino (ou -1 para sair): \n");
        
        printf("Linha Inicial:");
        scanf("%d", &start_row);

        printf("Coluna Inicial:");
        scanf("%d", &start_col);

        printf("Linha Final:");
        scanf("%d", &end_row);

        printf("Coluna Final:");
        scanf("%d", &end_col);

        if (start_row == -1) 
            break;
        
        if (movimento_permitido(start_row, start_col, end_row, end_col, tabuleiro)) {
            printf("Movimento valido!\n");
            alternar_jogador();
        } else {
            printf("Movimento invalido!\n");
        }
    }
    return 0;
}