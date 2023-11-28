#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um livro
typedef struct Livro {
    int codigo;
    char titulo[50];
    char assunto[100];
    char autor[50];
    struct Livro *proximo;
} Livro;

// Estrutura para representar um cliente
typedef struct Cliente {
    int codigo;
    char nome[50];
    Livro *livrosEmprestados;  // Lista encadeada de livros emprestados
    struct Cliente *proximo;
} Cliente;

// Função para adicionar um livro à lista de livros disponíveis
void adicionarLivro(Livro **listaLivros, int codigo, const char *titulo, const char *assunto, const char *autor) {
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    novoLivro->codigo = codigo;
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->assunto, assunto);
    strcpy(novoLivro->autor, autor);
    novoLivro->proximo = *listaLivros;
    *listaLivros = novoLivro;
}

// Função para adicionar um cliente à lista de clientes
void adicionarCliente(Cliente **listaClientes, int codigo, const char *nome) {
    Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
    novoCliente->codigo = codigo;
    strcpy(novoCliente->nome, nome);
    novoCliente->livrosEmprestados = NULL;  // Inicialmente, nenhum livro emprestado
    novoCliente->proximo = *listaClientes;
    *listaClientes = novoCliente;
}

// Função para emprestar um livro a um cliente
void emprestarLivro(Livro **listaLivrosDisponiveis, Cliente **listaClientes, int codigoLivro, int codigoCliente) {
    Livro *livroEmprestado = NULL;
    // Encontrar o livro na lista de livros disponíveis
    Livro *livroAtual = *listaLivrosDisponiveis;
    Livro *livroAnterior = NULL;
    while (livroAtual != NULL && livroAtual->codigo != codigoLivro) {
        livroAnterior = livroAtual;
        livroAtual = livroAtual->proximo;
    }

    if (livroAtual != NULL) {
        // Remover o livro da lista de livros disponíveis
        if (livroAnterior != NULL) {
            livroAnterior->proximo = livroAtual->proximo;
        } else {
            *listaLivrosDisponiveis = livroAtual->proximo;
        }

        // Adicionar o livro à lista de livros emprestados pelo cliente
        adicionarLivro(&(livroEmprestado), livroAtual->codigo, livroAtual->titulo, livroAtual->assunto, livroAtual->autor);

        // Encontrar o cliente na lista de clientes
        Cliente *clienteAtual = *listaClientes;
        while (clienteAtual != NULL && clienteAtual->codigo != codigoCliente) {
            clienteAtual = clienteAtual->proximo;
        }

        if (clienteAtual != NULL) {
            // Adicionar o livro emprestado à lista de livros emprestados pelo cliente
            livroEmprestado->proximo = clienteAtual->livrosEmprestados;
            clienteAtual->livrosEmprestados = livroEmprestado;
        } else {
            // Cliente não encontrado
            free(livroEmprestado);
            printf("Cliente não encontrado.\n");
        }

        // Liberar a memória do livro emprestado
        free(livroAtual);
        printf("Livro emprestado com sucesso.\n");
    } else {
        // Livro não encontrado
        printf("Livro não encontrado.\n");
    }
}

// Função para devolver um livro de um determinado cliente
void devolverLivro(Cliente **listaClientes, Livro **listaLivrosDisponiveis, int codigoLivro, int codigoCliente) {
    // Encontrar o cliente na lista de clientes
    Cliente *clienteAtual = *listaClientes;
    while (clienteAtual != NULL && clienteAtual->codigo != codigoCliente) {
        clienteAtual = clienteAtual->proximo;
    }

    if (clienteAtual != NULL) {
        // Encontrar o livro na lista de livros emprestados pelo cliente
        Livro *livroAtual = clienteAtual->livrosEmprestados;
        Livro *livroAnterior = NULL;

        while (livroAtual != NULL && livroAtual->codigo != codigoLivro) {
            livroAnterior = livroAtual;
            livroAtual = livroAtual->proximo;
        }

        if (livroAtual != NULL) {
            // Remover o livro da lista de livros emprestados pelo cliente
            if (livroAnterior != NULL) {
                livroAnterior->proximo = livroAtual->proximo;
            } else {
                clienteAtual->livrosEmprestados = livroAtual->proximo;
            }

            // Adicionar o livro de volta à lista de livros disponíveis
            adicionarLivro(listaLivrosDisponiveis, livroAtual->codigo, livroAtual->titulo, livroAtual->assunto, livroAtual->autor);

            // Liberar a memória do livro devolvido
            free(livroAtual);
            printf("Livro devolvido com sucesso.\n");
        } else {
            // Livro não encontrado nos livros emprestados pelo cliente
            printf("Livro não encontrado nos livros emprestados por este cliente.\n");
        }
    } else {
        // Cliente não encontrado
        printf("Cliente não encontrado.\n");
    }
}

// Função para imprimir os livros emprestados por um dado cliente
void imprimirLivrosEmprestados(Cliente *cliente) {
    if (cliente->livrosEmprestados == NULL) {
        printf("O cliente não possui livros emprestados.\n");
    } else {
        printf("Livros emprestados por %s:\n", cliente->nome);
        Livro *livroAtual = cliente->livrosEmprestados;
        while (livroAtual != NULL) {
            printf("Código: %d, Título: %s, Assunto: %s, Autor: %s\n", livroAtual->codigo, livroAtual->titulo, livroAtual->assunto, livroAtual->autor);
            livroAtual = livroAtual->proximo;
        }
    }
}

// Função para imprimir a lista de todos os clientes com seus livros emprestados
void imprimirClientes(Cliente *listaClientes) {
    if (listaClientes == NULL) {
        printf("Não há clientes cadastrados.\n");
    } else {
        Cliente *clienteAtual = listaClientes;
        while (clienteAtual != NULL) {
            printf("Cliente: %s (Código: %d)\n", clienteAtual->nome, clienteAtual->codigo);
            imprimirLivrosEmprestados(clienteAtual);
            printf("\n");
            clienteAtual = clienteAtual->proximo;
        }
    }
}

// Função para imprimir a lista de todos os livros emprestados
int imprimirLivrosEmprestadosGeral(Cliente *listaClientes) {
    int temLivros = 0;  //assume inicialmente que não há livros emprestados

    Cliente *clienteAtual = listaClientes;
    while (clienteAtual != NULL) {
        if (clienteAtual->livrosEmprestados != NULL) {
            temLivros = 1;  //há pelo menos um livro emprestado
            break;
        }
        clienteAtual = clienteAtual->proximo;
    }

    return temLivros;
}

// Função para imprimir a lista de livros disponíveis
void imprimirLivrosDisponiveis(Livro *listaLivros) {
    if(listaLivros == NULL){
        printf("Não existem livros cadastrados no sistema.\n");
    }else{
        printf("Livros Disponíveis:\n");
        Livro *livroAtual = listaLivros;
        while (livroAtual != NULL) {
            printf("Código: %d, Título: %s, Assunto: %s, Autor: %s\n", livroAtual->codigo, livroAtual->titulo, livroAtual->assunto, livroAtual->autor);
            livroAtual = livroAtual->proximo;
        }
    }
}

// Função principal
int main() {
    Livro *livrosDisponiveis = NULL;
    Cliente *clientes = NULL;

    int opcao;
    do {
        printf("\n1. Inserir um livro novo na biblioteca\n");
        printf("2. Inserir um novo cliente\n");
        printf("3. Emprestar um livro para um cliente\n");
        printf("4. Devolver um livro de um determinado cliente\n");
        printf("5. Imprimir os livros que estão emprestados por um dado cliente\n");
        printf("6. Imprimir a Lista de todos os clientes com os respectivos livros emprestados\n");
        printf("7. Imprimir a Lista de Todos os Livros Emprestados\n");
        printf("8. Imprimir a lista de Livros Disponíveis da Biblioteca\n");
        printf("9. Sair do Sistema\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int codigo;
                char titulo[50], assunto[100], autor[50];
                printf("Digite o código do livro: ");
                scanf("%d", &codigo);
                getchar(); //consume o caractere de nova linha pendente no buffer, fazendo com que a proxima leitura não seja afetada
                printf("Digite o título do livro: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; //remove a quebra de linha (se existir)
                printf("Digite o assunto do livro: ");
                fgets(assunto, sizeof(assunto), stdin);
                assunto[strcspn(assunto, "\n")] = '\0'; //remove a quebra de linha (se existir)
                printf("Digite o autor do livro: ");
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = '\0'; //remove a quebra de linha (se existir)
                adicionarLivro(&livrosDisponiveis, codigo, titulo, assunto, autor);
                printf("Livro adicionado com sucesso.\n");
                break;
            }
            case 2: {
                int codigo;
                char nome[50];
                printf("Digite o código do cliente: ");
                scanf("%d", &codigo);
                getchar(); //consume o caractere de nova linha pendente no buffer, fazendo com que a proxima leitura não seja afetada
                printf("Digite o nome do cliente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; //remove a quebra de linha (se existir)
                adicionarCliente(&clientes, codigo, nome);
                printf("Cliente adicionado com sucesso.\n");
                break;
            }
            case 3: {
                int codigoLivro, codigoCliente;
                printf("Digite o código do livro a ser emprestado: ");
                scanf("%d", &codigoLivro);
                printf("Digite o código do cliente: ");
                scanf("%d", &codigoCliente);
                emprestarLivro(&livrosDisponiveis, &clientes, codigoLivro, codigoCliente);
                break;
            }
            case 4: {
                int codigoLivro, codigoCliente;
                printf("Digite o código do livro a ser devolvido: ");
                scanf("%d", &codigoLivro);
                printf("Digite o código do cliente: ");
                scanf("%d", &codigoCliente);
                devolverLivro(&clientes, &livrosDisponiveis, codigoLivro, codigoCliente);
                break;
            }
            case 5: {
                int codigoCliente;
                printf("Digite o código do cliente: ");
                scanf("%d", &codigoCliente);
                // Encontrar o cliente na lista de clientes
                Cliente *clienteAtual = clientes;
                while (clienteAtual != NULL && clienteAtual->codigo != codigoCliente) {
                    clienteAtual = clienteAtual->proximo;
                }
                if (clienteAtual != NULL) {
                    imprimirLivrosEmprestados(clienteAtual);
                } else {
                    // Cliente não encontrado
                    printf("Cliente não encontrado.\n");
                }
                break;
            }
            case 6: {
                imprimirClientes(clientes);
                break;
            }
            case 7: {
                if(!imprimirLivrosEmprestadosGeral(clientes)){
                    printf("Não há nenhum livro emprestado.\n");
                }
                break;
            }
            case 8: {
                imprimirLivrosDisponiveis(livrosDisponiveis);
                break;
            }
            case 9:
                printf("Saindo do Sistema. Obrigado!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 9);

    // Liberar a memória alocada
    Livro *livroAtual = livrosDisponiveis;
    while (livroAtual != NULL) {
        Livro *proximoLivro = livroAtual->proximo;
        free(livroAtual);
        livroAtual = proximoLivro;
    }

    Cliente *clienteAtual = clientes;
    while (clienteAtual != NULL) {
        Cliente *proximoCliente = clienteAtual->proximo;
        Livro *livroAtual = clienteAtual->livrosEmprestados;
        while (livroAtual != NULL) {
            Livro *proximoLivro = livroAtual->proximo;
            free(livroAtual);
            livroAtual = proximoLivro;
        }
        free(clienteAtual);
        clienteAtual = proximoCliente;
    }

    return 0;
}