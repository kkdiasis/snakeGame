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

// prototipos
void gerarComida();
void inicializar();
void desenharTela();
void processarEntrada();
void atualizar();