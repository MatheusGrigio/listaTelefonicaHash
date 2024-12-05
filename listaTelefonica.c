#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_TABELA 10
#define TAMANHO_NOME 50
#define TAMANHO_TELEFONE 20


typedef struct Contato {
    char nome[TAMANHO_NOME];
    char telefone[TAMANHO_TELEFONE];
    struct Contato* proximo;
} Contato;


int funcao_hash(const char* nome) {
    int hash = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        hash = (hash * 31 + nome[i]) % TAMANHO_TABELA;
    }
    return hash;
}


void adicionar_contato(Contato* tabela[], const char* nome, const char* telefone) {
    int indice = funcao_hash(nome);
    Contato* novo = (Contato*)malloc(sizeof(Contato));
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
    printf("Contato adicionado.\n");
}


void buscar_contato(Contato* tabela[], const char* nome) {
    int indice = funcao_hash(nome);
    Contato* atual = tabela[indice];

    clock_t inicio = clock(); // mostra tempo

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            clock_t fim = clock();
            double tempo = ((double)(fim - inicio)) * 1000 / CLOCKS_PER_SEC;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", nome, atual->telefone, tempo);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void remover_contato(Contato* tabela[], const char* nome) {
    int indice = funcao_hash(nome);
    Contato* atual = tabela[indice];
    Contato* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                tabela[indice] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Contato removido.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void exibir_todos_contatos(Contato* tabela[]) {
    printf("Lista de contatos:\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato* atual = tabela[i];
        while (atual != NULL) {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}

void liberar_memoria(Contato* tabela[]) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Contato* atual = tabela[i];
        while (atual != NULL) {
            Contato* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
}

// menu 
void menu() {
    Contato* tabela[TAMANHO_TABELA] = {NULL}; // cria tabela hash

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        
        int opcao;
        scanf("%d", &opcao);
        getchar(); //limpa o buffer!
    
        if (opcao == 0) {
            printf("Encerrando o programa...\n");
            liberar_memoria(tabela);
            break;
        }

        char nome[TAMANHO_NOME];
        char telefone[TAMANHO_TELEFONE];

        switch (opcao) {
        case 1:
            printf("Nome: ");
            fgets(nome, TAMANHO_NOME, stdin);
            nome[strcspn(nome, "\n")] = '\0'; 
            printf("Telefone: ");
            fgets(telefone, TAMANHO_TELEFONE, stdin);
            telefone[strcspn(telefone, "\n")] = '\0'; 
            adicionar_contato(tabela, nome, telefone);
            break;
        case 2:
            printf("Nome: ");
            fgets(nome, TAMANHO_NOME, stdin);
            nome[strcspn(nome, "\n")] = '\0'; 
            buscar_contato(tabela, nome);
            break;
        case 3:
            printf("Nome: ");
            fgets(nome, TAMANHO_NOME, stdin);
            nome[strcspn(nome, "\n")] = '\0'; 
            remover_contato(tabela, nome);
            break;
        case 4:
            exibir_todos_contatos(tabela);
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
