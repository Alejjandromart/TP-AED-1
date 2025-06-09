# TP-AED-1

<img src="https://github.com/user-attachments/assets/c6eda301-3d87-4e44-af7d-34876e04314a" alt="Descrição da imagem" width="150" height="150"><img src="https://github.com/user-attachments/assets/24a338b6-4a64-49f3-979a-73b645b30712" alt="logo do icet" width="150" height="150">



# TP - AVALIAÇÃO DE AED-1

**Curso:** Engenharia de Software  
**Docente:** Prof. Alternei de Souza Brito
## Integrantes

- **Alejjandro Martins Dutra** 
- **Dieglison Correia Varejão** 
- **Sergio Fernandes Mar Filho**


## 1. Função Hash Utilizada

A função hash implementada no sistema é baseada na **operação módulo**:

```c
int hash(int matricula) {
    return matricula % TABLE_SIZE;
}
```

**Características:**
- **Tipo:** Divisão (método do módulo)
- **Tamanho da tabela:** 10 buckets (TABLE_SIZE = 10)
- **Entrada:** Matrícula do aluno (número inteiro)
- **Saída:** Índice do bucket (0 a 9)
- **Tratamento de colisões:** Encadeamento (chaining) com listas ligadas

**Exemplos de mapeamento:**
- Matrícula 12345 → hash(12345) = 12345 % 10 = **5**
- Matrícula 67890 → hash(67890) = 67890 % 10 = **0**
- Matrícula 11111 → hash(11111) = 11111 % 10 = **1**

## 2. Análise dos Buckets Após Inserções

### Cenário de Exemplo: Inserindo 5 Alunos

**Inserções simuladas:**

1. **Aluno 1:** Matrícula 12345 → Bucket 5
2. **Aluno 2:** Matrícula 67890 → Bucket 0  
3. **Aluno 3:** Matrícula 54321 → Bucket 1
4. **Aluno 4:** Matrícula 11115 → Bucket 5 (COLISÃO!)
5. **Aluno 5:** Matrícula 22225 → Bucket 5 (COLISÃO!)

### Estado dos Buckets:

```
Bucket[0]: 67890 (João Silva) -> NULL
Bucket[1]: 54321 (Maria Santos) -> NULL
Bucket[2]: NULL
Bucket[3]: NULL
Bucket[4]: NULL
Bucket[5]: 22225 (Pedro Costa) -> 11115 (Ana Oliveira) -> 12345 (Carlos Lima) -> NULL
Bucket[6]: NULL
Bucket[7]: NULL
Bucket[8]: NULL
Bucket[9]: NULL
```

**Observações:**
- **Buckets ocupados:** 3 de 10 (30%)
- **Buckets vazios:** 7 de 10 (70%)
- **Bucket com mais colisões:** Bucket 5 (3 alunos)
- **Fator de carga:** 5/10 = 0.5

## 3. Explicação das Funções

### 3.1 Funções de Estrutura e Inicialização

#### `HashTable* criar_tabela()`
**Propósito:** Inicializa uma nova tabela hash vazia.
**Funcionamento:**
- Aloca memória para a estrutura HashTable
- Define o tamanho da tabela como TABLE_SIZE (10)
- Inicializa todos os buckets como NULL usando calloc()
- Retorna ponteiro para a tabela criada

**Complexidade:** O(n) onde n é o tamanho da tabela

#### `Aluno* criar_aluno(int matricula, const char *nome, const char *curso)`

**Propósito:** Cria um novo nó para a lista encadeada.
**Funcionamento:**
- Aloca memória para um novo aluno
- Copia os dados recebidos para a estrutura
- Inicializa o ponteiro próximo como NULL
- Retorna o ponteiro para o novo aluno

**Complexidade:** O(1)

#### `void limparBuffer()`

**Propósito:** Remove caracteres residuais do buffer de entrada.
**Funcionamento:**
- Consome todos os caracteres até encontrar '\n'
- Evita problemas com entradas mistas (scanf + fgets)

### 3.2 Funções Principais de Manipulação

#### `void inserir_aluno(HashTable *tabela)`

**Propósito:** Adiciona um novo aluno à tabela hash.
**Funcionamento:**
1. Lê os dados do aluno (matrícula, nome, curso)
2. Calcula o índice usando a função hash
3. Verifica se a matrícula já existe no bucket
4. Se não existir, cria novo aluno e insere no início da lista
5. Atualiza o ponteiro do bucket

**Tratamento de colisões:** Inserção no início da lista encadeada
**Complexidade:** O(k) onde k é o número de elementos no bucket

#### `void remover_aluno(HashTable *tabela)`

**Propósito:** Remove um aluno específico da tabela.
**Funcionamento:**
1. Lê a matrícula do aluno a ser removido
2. Calcula o índice do bucket
3. Percorre a lista encadeada procurando a matrícula
4. Remove o nó e reconecta a lista
5. Libera a memória do aluno removido

**Casos especiais:**
- Remoção do primeiro elemento da lista
- Remoção de elementos no meio ou fim da lista
**Complexidade:** O(k) onde k é o número de elementos no bucket

#### `void buscar_aluno(HashTable *tabela)`

**Propósito:** Localiza e exibe os dados de um aluno específico.
**Funcionamento:**
1. Lê a matrícula desejada
2. Calcula o índice do bucket
3. Percorre a lista encadeada até encontrar a matrícula
4. Exibe os dados completos do aluno

**Complexidade:** O(k) onde k é o número de elementos no bucket

### 3.3 Funções de Visualização e Análise

#### `void exibir_tabela(HashTable *tabela)`

**Propósito:** Mostra a estrutura completa da tabela hash.
**Funcionamento:**
- Percorre todos os buckets da tabela
- Para cada bucket, exibe todos os alunos na lista encadeada
- Mostra a sequência de ponteiros (visualização da estrutura)

**Utilidade:** Debug e compreensão da distribuição dos dados

#### `void exibir_estatisticas(HashTable *tabela)`

**Propósito:** Fornece métricas sobre a performance da tabela.
**Funcionamento:**
1. Conta o total de alunos em todos os buckets
2. Identifica buckets vazios e ocupados
3. Encontra o bucket com mais colisões
4. Calcula estatísticas de distribuição

**Métricas fornecidas:**
- Total de alunos
- Buckets vazios
- Bucket com mais colisões
- Distribuição por bucket

### 3.4 Função de Gerenciamento de Memória

#### `void liberar_tabela(HashTable *tabela)`

**Propósito:** Libera toda a memória alocada pela tabela.
**Funcionamento:**
1. Percorre todos os buckets
2. Para cada bucket, libera todos os nós da lista encadeada
3. Libera o array de buckets
4. Libera a estrutura da tabela

**Importância:** Evita vazamentos de memória (memory leaks)

## 4. Execução das Funcionalidades

### 4.1 Inserir Aluno

```
=== MENU PRINCIPAL ===
1. Inserir Aluno
Escolha uma opção: 1

--- Inserir Aluno ---
Matrícula: 12345
Nome: Carlos Lima
Curso: Engenharia de Software
Aluno inserido com sucesso!
```

### 4.2 Buscar Aluno

```
=== MENU PRINCIPAL ===
3. Buscar Aluno
Escolha uma opção: 3

--- Buscar Aluno ---
Matrícula: 12345

Dados do Aluno:
Matrícula: 12345
Nome: Carlos Lima
Curso: Engenharia de Software
```

### 4.3 Exibir Tabela Hash

```
=== MENU PRINCIPAL ===
4. Exibir Tabela Hash
Escolha uma opção: 4

--- Tabela Hash ---
Bucket[0]: 67890 (João Silva) -> NULL
Bucket[1]: 54321 (Maria Santos) -> NULL
Bucket[2]: NULL
Bucket[3]: NULL
Bucket[4]: NULL
Bucket[5]: 22225 (Pedro Costa) -> 11115 (Ana Oliveira) -> 12345 (Carlos Lima) -> NULL
Bucket[6]: NULL
Bucket[7]: NULL
Bucket[8]: NULL
Bucket[9]: NULL
```

### 4.4 Exibir Estatísticas

```
=== MENU PRINCIPAL ===
5. Exibir Estatísticas
Escolha uma opção: 5

--- Estatísticas ---
Total de alunos: 5
Quantidade de buckets: 10
Buckets vazios: 7
Bucket com mais colisões: 5 (3 alunos)

Alunos por bucket:
Bucket[0]: 1 aluno(s)
Bucket[1]: 1 aluno(s)
Bucket[2]: 0 aluno(s)
Bucket[3]: 0 aluno(s)
Bucket[4]: 0 aluno(s)
Bucket[5]: 3 aluno(s)
Bucket[6]: 0 aluno(s)
Bucket[7]: 0 aluno(s)
Bucket[8]: 0 aluno(s)
Bucket[9]: 0 aluno(s)
```

### 4.5 Remover Aluno

```
=== MENU PRINCIPAL ===
2. Remover Aluno
Escolha uma opção: 2

--- Remover Aluno ---
Matrícula: 11115
Aluno removido com sucesso!
```

## 5. Análise de Performance e Eficiência

### Complexidade das Operações:

- **Inserção:** O(1) caso médio, O(n) pior caso
- **Busca:** O(1) caso médio, O(n) pior caso  
- **Remoção:** O(1) caso médio, O(n) pior caso

### Fatores que Afetam a Performance:

1. **Qualidade da função hash:** A função módulo pode causar clustering
2. **Fator de carga:** Razão entre elementos inseridos e tamanho da tabela
3. **Distribuição das chaves:** Matrículas com padrões podem causar mais colisões

### Vantagens do Sistema:

- **Simplicidade:** Implementação clara e fácil de entender
- **Eficiência:** Acesso rápido na maioria dos casos práticos
- **Flexibilidade:** Suporta número variável de alunos por bucket
- **Robustez:** Tratamento adequado de colisões e casos especiais

### Limitações Identificadas:

- **Tamanho fixo:** Tabela não redimensiona automaticamente
- **Função hash simples:** Pode causar distribuição não uniforme
- **Sem balanceamento:** Não há rebalanceamento automático

## 6. Conclusão

O sistema implementado demonstra uma aplicação prática de tabelas hash para gerenciamento de dados acadêmicos. A arquitetura escolhida, baseada em encadeamento separado (separate chaining), oferece uma solução para o problema de colisões, garantindo que todos os alunos sejam armazenados mesmo quando suas matrículas mapeiam para o mesmo bucket.

**Aspectos Técnicos Destacados:**

A função hash por divisão (módulo), embora simples, proporciona uma distribuição razoável dos dados quando as matrículas não seguem padrões específicos. O uso de listas encadeadas como estrutura secundária permite flexibilidade no número de elementos por bucket, adaptando-se dinamicamente à carga de trabalho.

**Qualidade da Implementação:**

O código demonstra boas práticas de programação, incluindo verificação de duplicatas, tratamento de casos especiais (como remoção do primeiro elemento), gerenciamento adequado de memória e interface de usuário intuitiva. As funções de estatísticas fornecem insights valiosos sobre a performance e distribuição dos dados.

**Aplicabilidade Prática:**

Este sistema é adequado para cenários educacionais de pequeno a médio porte, onde o número de alunos não excede significativamente o tamanho da tabela. Para aplicações em larga escala, seria recomendável implementar redimensionamento dinâmico e funções hash mais sofisticadas.

**Valor Educacional:**

A implementação serve como excelente exemplo didático, demonstrando conceitos fundamentais de estruturas de dados como hashing, listas encadeadas, gerenciamento de memória e análise de complexidade. A visualização clara da estrutura interna através das funções de exibição facilita a compreensão do funcionamento da tabela hash.

Em suma, este projeto representa uma implementação bem-sucedida de uma estrutura de dados fundamental, combinando eficiência computacional com clareza conceitual, tornando-se uma ferramenta valiosa tanto para aplicações práticas quanto para fins educacionais.
