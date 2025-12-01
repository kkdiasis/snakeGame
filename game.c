#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LARGURA 40
#define ALTURA 20
#define TAMANHO_MAX 100

typedef struct
{
    int y[TAMANHO_MAX];
    int x[TAMANHO_MAX];
    int comprimento;
    int direcaox;
    int direcaoy;

} Cobra;

Cobra cobra;
bool gameover = false;
char telaBuffer[ALTURA][LARGURA]; // criando um buffer para tela

void inicializar() // utilizando ncurses
{
    initscr();            // inicia a tela
    cbreak();             // habilita ctrl+c para fechar
    noecho();             // não ecoa as teclas
    keypad(stdscr, true); // trabalha com teclas não alfanuméricas, utilizaremos as setas do pad
    curs_set(0);          // desabilita cursor do mouse
    start_color();        // habilita cores no terminal

    // iniciando os pares de cores
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);

    // propriedades iniciais da cobra
    cobra.comprimento = 1;
    cobra.x[0] = LARGURA / 2;
    cobra.y[0] = ALTURA / 2;
    cobra.direcaox = 1;
    cobra.direcaoy = 0;

    // inicializando bufer da tela
    for (int i = 0; i < ALTURA; i++)
    {
        for (int j = 0; j < LARGURA; j++)
        {
            if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1)
                telaBuffer[i][j] = '#';

            telaBuffer[i][j] = ' ';
        }
    }
}

int main(void)
{
    inicializar();

    while (!gameover)
    {
    }

    return 0;
}