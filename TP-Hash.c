#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define TABLE_SIZE 10

typedef struct Aluno {
    int matricula;
    char nome[100];
    char curso[50];
    struct Aluno *prox;
} Aluno;

typedef struct {
    Aluno **buckets;
    int tamanho;
} HashTable;

// Funções auxiliares
void limparBuffer() {
    while (getchar() != '\n');
}

// Função para criar a tabela hash
HashTable* criar_tabela() {
    HashTable *tabela = (HashTable*)malloc(sizeof(HashTable));
    tabela->tamanho = TABLE_SIZE;
    tabela->buckets = (Aluno**)calloc(tabela->tamanho, sizeof(Aluno*));
    return tabela;
}

// Função hash
int hash(int matricula) {
    return matricula % TABLE_SIZE;
}

// Função para criar um novo aluno
Aluno* criar_aluno(int matricula, const char *nome, const char *curso) {
    Aluno *novo = (Aluno*)malloc(sizeof(Aluno));
    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    strcpy(novo->curso, curso);
    novo->prox = NULL;
    return novo;
}

// 1. Inserir Aluno
void inserir_aluno(HashTable *tabela) {
    int matricula;
    char nome[100], curso[50];
    
    printf("\n--- Inserir Aluno ---\n");
    printf("Matrícula: ");
    scanf("%d", &matricula);
    limparBuffer();
    
    // Verificar se matrícula já existe
    int indice = hash(matricula);
    Aluno *atual = tabela->buckets[indice];
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            printf("Erro: Matrícula já existente!\n");
            return;
        }
        atual = atual->prox;
    }
    
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    
    printf("Curso: ");
    fgets(curso, sizeof(curso), stdin);
    curso[strcspn(curso, "\n")] = '\0';
    
    Aluno *novo = criar_aluno(matricula, nome, curso);
    
    // Inserir no início da lista encadeada
    novo->prox = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
    
    printf("Aluno inserido com sucesso!\n");
}

// 2. Remover Aluno
void remover_aluno(HashTable *tabela) {
    int matricula;
    
    printf("\n--- Remover Aluno ---\n");
    printf("Matrícula: ");
    scanf("%d", &matricula);
    limparBuffer();
    
    int indice = hash(matricula);
    Aluno *atual = tabela->buckets[indice];
    Aluno *anterior = NULL;
    
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            if (anterior == NULL) {
                // Remover do início da lista
                tabela->buckets[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Aluno removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    
    printf("Aluno não encontrado!\n");
}

// 3. Buscar Aluno
void buscar_aluno(HashTable *tabela) {
    int matricula;
    
    printf("\n--- Buscar Aluno ---\n");
    printf("Matrícula: ");
    scanf("%d", &matricula);
    limparBuffer();
    
    int indice = hash(matricula);
    Aluno *atual = tabela->buckets[indice];
    
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            printf("\nDados do Aluno:\n");
            printf("Matrícula: %d\n", atual->matricula);
            printf("Nome: %s\n", atual->nome);
            printf("Curso: %s\n", atual->curso);
            return;
        }
        atual = atual->prox;
    }
    
    printf("Aluno não encontrado!\n");
}

// 4. Exibir Tabela Hash
void exibir_tabela(HashTable *tabela) {
    printf("\n--- Tabela Hash ---\n");
    for (int i = 0; i < tabela->tamanho; i++) {
        printf("Bucket[%d]: ", i);
        Aluno *atual = tabela->buckets[i];
        while (atual != NULL) {
            printf("%d (%s) -> ", atual->matricula, atual->nome);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

// 5. Exibir Estatísticas
void exibir_estatisticas(HashTable *tabela) {
    printf("\n--- Estatísticas ---\n");
    
    int total_alunos = 0;
    int bucket_mais_colisoes = 0;
    int max_colisoes = -1;
    int buckets_vazios = 0;
    
    for (int i = 0; i < tabela->tamanho; i++) {
        int alunos_no_bucket = 0;
        Aluno *atual = tabela->buckets[i];
        
        while (atual != NULL) {
            alunos_no_bucket++;
            atual = atual->prox;
        }
        
        total_alunos += alunos_no_bucket;
        
        if (alunos_no_bucket == 0) {
            buckets_vazios++;
        }
        
        if (alunos_no_bucket > max_colisoes) {
            max_colisoes = alunos_no_bucket;
            bucket_mais_colisoes = i;
        }
    }
    
    printf("Total de alunos: %d\n", total_alunos);
    printf("Quantidade de buckets: %d\n", tabela->tamanho);
    printf("Buckets vazios: %d\n", buckets_vazios);
    printf("Bucket com mais colisões: %d (%d alunos)\n", bucket_mais_colisoes, max_colisoes);
    
    printf("\nAlunos por bucket:\n");
    for (int i = 0; i < tabela->tamanho; i++) {
        int alunos_no_bucket = 0;
        Aluno *atual = tabela->buckets[i];
        
        while (atual != NULL) {
            alunos_no_bucket++;
            atual = atual->prox;
        }
        
        printf("Bucket[%d]: %d aluno(s)\n", i, alunos_no_bucket);
    }
}

// Liberar memória
void liberar_tabela(HashTable *tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        Aluno *atual = tabela->buckets[i];
        while (atual != NULL) {
            Aluno *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(tabela->buckets);
    free(tabela);
}

int main() {
    HashTable *tabela = criar_tabela();
    int opcao;
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Inserir Aluno\n");
        printf("2. Remover Aluno\n");
        printf("3. Buscar Aluno\n");
        printf("4. Exibir Tabela Hash\n");
        printf("5. Exibir Estatísticas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                inserir_aluno(tabela);
                break;
            case 2:
                remover_aluno(tabela);
                break;
            case 3:
                buscar_aluno(tabela);
                break;
            case 4:
                exibir_tabela(tabela);
                break;
            case 5:
                exibir_estatisticas(tabela);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);
    
    liberar_tabela(tabela);
    return 0;
}
