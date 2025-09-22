#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura para representar uma peça do jogo
typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // Identificador único da peça
} Peca;

// Constantes para a fila circular
#define MAX 5  // Tamanho fixo da fila (5 peças)

// Variáveis globais para gerenciar a fila circular
Peca fila[MAX];     // Array que armazena as peças
int front = 0;      // Índice da frente da fila
int rear = 0;       // Índice do final da fila (aponta para o próximo espaço livre)
int count = 0;      // Contador de elementos na fila

// Variáveis para geração de peças
int next_id = 0;    // Próximo ID a ser atribuído
char tipos[] = {'I', 'O', 'T', 'L'};  // Tipos possíveis de peças

// Função para gerar uma nova peça automaticamente
// Escolhe um tipo aleatório e atribui um ID único incremental
Peca gerarPeca() {
    Peca p;
    p.nome = tipos[rand() % 4];  // Seleciona um tipo aleatoriamente
    p.id = next_id++;            // Atribui ID único
    return p;
}

// Verifica se a fila está vazia
int isEmpty() {
    return count == 0;
}

// Verifica se a fila está cheia
int isFull() {
    return count == MAX;
}

// Insere uma nova peça no final da fila (enqueue)
// Usa aritmética modular para implementar fila circular
void enqueue(Peca p) {
    if (isFull()) {
        printf("Fila cheia! Não é possível inserir mais peças.\n");
        return;
    }
    fila[rear] = p;
    rear = (rear + 1) % MAX;  // Avança o rear de forma circular
    count++;
    printf("Inseriu peça [%c %d]\n", p.nome, p.id);
}

// Remove e retorna a peça da frente da fila (dequeue)
// Usa aritmética modular para implementar fila circular
Peca dequeue() {
    if (isEmpty()) {
        printf("Fila vazia! Não é possível jogar uma peça.\n");
        // Retorna uma peça inválida em caso de erro (pode ser ajustado conforme necessidade)
        Peca p = {' ', -1};
        return p;
    }
    Peca p = fila[front];
    front = (front + 1) % MAX;  // Avança o front de forma circular
    count--;
    printf("Jogou peça [%c %d]\n", p.nome, p.id);
    return p;
}

// Exibe o estado atual da fila
// Percorre a fila a partir do front, usando aritmética modular para ordem correta
void display() {
    if (isEmpty()) {
        printf("Fila vazia\n");
        return;
    }
    printf("Fila de peças\n");
    int i = front;
    for (int j = 0; j < count; j++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX;  // Avança circularmente
    }
    printf("\n");
}

// Função para inicializar a fila
// Gera 5 peças iniciais e as insere na fila
void inicializar() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    front = 0;
    rear = 0;
    count = 0;
    next_id = 0;
    // Insere 5 peças iniciais
    for (int i = 0; i < MAX; i++) {
        Peca p = gerarPeca();
        enqueue(p);  // Usa a função enqueue para consistência
    }
}

int main() {
    int opcao;
    Peca pecaRemovida;  // Variável para armazenar peça removida (se necessário)

    inicializar();  // Inicializa a fila com 5 peças
    display();      // Exibe o estado inicial

    // Loop principal do menu
    do {
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Jogar peça (dequeue)
            if (!isEmpty()) {
                pecaRemovida = dequeue();
            }
            // Exibe o estado após a ação
            display();
        } else if (opcao == 2) {
            // Inserir nova peça (enqueue)
            if (!isFull()) {
                Peca novaPeca = gerarPeca();
                enqueue(novaPeca);
            }
            // Exibe o estado após a ação
            display();
        } else if (opcao == 0) {
            printf("Saindo do programa.\n");
            break;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (1);

    return 0;
}
