#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LARGURA 40
#define ALTURA 20
#define TAMANHO_MAX 100
#define ESPERA_PADRAO 200
#define PAREDE '#'
#define COMIDA '@'
#define COBRA '$'
#define COR_COBRA 1
#define COR_COMIDA 2
#define COR_PAREDE 3

typedef struct
{
    int y[TAMANHO_MAX];
    int x[TAMANHO_MAX];
    int comprimento;
    int direcaox;
    int direcaoy;

} Cobra;

typedef struct
{
    int x;
    int y;
} Comida;

// Globais
Cobra cobra;
Comida comida;
bool gameover = false;
char telaBuffer[ALTURA][LARGURA]; // criando um buffer para tela
int score = 0;

// prototipos
void gerarComida();
void inicializar();
void desenharTela();
void processarEntrada();
void atualizar();

int main(void)
{
    srand(time(NULL));

    inicializar();

    while (!gameover) // loop principal do jogo
    {
        desenharTela();
        processarEntrada();
        atualizar();

        napms(ESPERA_PADRAO); // aguarda, valor em milisegundos.
    }

    printf("\nBAI BAI!\n");

    return 0;
}

void gerarComida()
{
    comida.x = rand() % (LARGURA - 2) + 1;
    comida.y = rand() % (ALTURA - 2) + 1;
}

void inicializar() // utilizando ncurses
{
    initscr();             // inicia a tela
    cbreak();              // habilita ctrl+c para fechar
    nodelay(stdscr, true); // ativa o modo de não espera para a tela padrão (stdscr), o que significa que as funções de leitura de entrada, como getch(), retornarão imediatamente em vez de bloquear até que um caractere seja inserido. Se nenhum caractere estiver pronto, getch() retornará um valor especial (normalmente -1) para indicar que não há entrada disponível.
    noecho();              // não ecoa as teclas
    keypad(stdscr, true);  // trabalha com teclas não alfanuméricas, utilizaremos as setas do pad
    curs_set(0);           // desabilita cursor do mouse
    start_color();         // habilita cores no terminal

    // iniciando os pares de cores
    init_pair(COR_COBRA, COLOR_GREEN, COLOR_BLACK);
    init_pair(COR_COMIDA, COLOR_RED, COLOR_BLACK);
    init_pair(COR_PAREDE, COLOR_CYAN, COLOR_BLACK);

    // propriedades iniciais da cobra
    cobra.comprimento = 1;
    cobra.x[0] = LARGURA / 2;
    cobra.y[0] = ALTURA / 2;
    cobra.direcaox = 1;
    cobra.direcaoy = 0;

    // gerando a posição da comida na tela
    gerarComida();

    // inicializando bufer da tela
    for (int i = 0; i < ALTURA; i++)
    {
        for (int j = 0; j < LARGURA; j++)
        {
            if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1)
                telaBuffer[i][j] = PAREDE;
            else
                telaBuffer[i][j] = ' ';
        }
    }
}

void desenharTela()
{
    // Este loop vai limpando o rastro da cobrinha e deixando desenhado somente as bordas e a cobrinha em seu tamanho atual
    for (int i = 1; i < ALTURA - 1; i++)
    {
        for (int j = 1; j < LARGURA - 1; j++)
        {
            if (i == 0 || i == ALTURA - 1 || j == 0 || j == LARGURA - 1)
                telaBuffer[i][j] = PAREDE;
            else
                telaBuffer[i][j] = ' ';
        }
    }

    // desenhar comida
    telaBuffer[comida.y][comida.x] = COMIDA;

    // desenha a cobrinha em seu tamanho atual
    for (int i = 0; i < cobra.comprimento; i++)
    {
        telaBuffer[cobra.y[i]][cobra.x[i]] = COBRA;
    }

    // deseha a tela atualizada
    for (int i = 0; i < ALTURA; i++)
    {
        for (int j = 0; j < LARGURA; j++)
        {
            if(telaBuffer[i][j] == PAREDE)
            {
                attron(COLOR_PAIR(COR_PAREDE));
                mvaddch(i, j, telaBuffer[i][j]); // função da lib sncurses para immprimir caracteres na tela
                attroff(COLOR_PAIR(COR_PAREDE));
            }
            else if(telaBuffer[i][j] == COBRA)
            {
                attron(COLOR_PAIR(COR_COBRA));
                mvaddch(i, j, telaBuffer[i][j]); // função da lib sncurses para immprimir caracteres na tela
                attroff(COLOR_PAIR(COR_COBRA));
                
            }
            else if(telaBuffer[i][j] == COMIDA)
            {
                attron(COLOR_PAIR(COR_COMIDA));
                mvaddch(i, j, telaBuffer[i][j]); // função da lib sncurses para immprimir caracteres na tela
                attroff(COLOR_PAIR(COR_COMIDA));
                
            }
            else
                mvaddch(i, j, telaBuffer[i][j]); // função da lib sncurses para immprimir caracteres na tela
            
        }
    }
    mvprintw(ALTURA, 0, "SCORE: %d", score); // adiciona o score na tela
    refresh();
}

void atualizar() // Movimmentando a cobrinha
{
    int novoX = cobra.x[0] + cobra.direcaox;
    int novoY = cobra.y[0] + cobra.direcaoy;

    if (novoX <= 0 || novoX >= LARGURA - 1 || novoY <= 0 || novoY >= ALTURA - 1)
    {
        gameover = true;
    }

    if (novoX == comida.x && novoY == comida.y)
    {
        cobra.comprimento++;
        score += 10;
        gerarComida();
    }

    for (int i = cobra.comprimento - 1; i > 0; i--)
    {
        cobra.x[i] = cobra.x[i - 1];
        cobra.y[i] = cobra.y[i - 1];
    }

    cobra.x[0] = novoX;
    cobra.y[0] = novoY;
}

void processarEntrada()
{
    int tecla = getch();

    switch (tecla)
    {
    case KEY_UP:
        if (cobra.direcaoy == 0)
            cobra.direcaoy = -1;
        cobra.direcaox = 0;
        break;

    case KEY_DOWN:
        if (cobra.direcaoy == 0)
            cobra.direcaoy = 1;
        cobra.direcaox = 0;
        break;

    case KEY_RIGHT:
        if (cobra.direcaox == 0)
            cobra.direcaox = 1;
        cobra.direcaoy = 0;
        break;

    case KEY_LEFT:
        if (cobra.direcaox == 0)
            cobra.direcaox = -1;
        cobra.direcaoy = 0;
        break;

    case 'q':
    case 'Q':
        gameover = true;
        break;
    }
}