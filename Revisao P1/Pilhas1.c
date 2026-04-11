#include <stdio.h>
#include <stdlib.h>

typedef struct node_pilha{
    int dado;
    struct node_pilha *prox;
} Tnode_pilha;

int Inicializar_Pilha(Tnode_pilha **inicio);
int Inserir_topo(Tnode_pilha **inicio, int novoDado);
int Remover_topo(Tnode_pilha **inicio);
int Obter_topo(Tnode_pilha *inicio, int *dado);
int Verifica_vazio(Tnode_pilha *inicio, int *resp);
int Listar(Tnode_pilha *P1);
int Juntar_pilhas(Tnode_pilha **P1, Tnode_pilha **P2, Tnode_pilha **P3);

int main(void)
{
    int info;
    int erro, resposta;
    Tnode_pilha *ini;
    Tnode_pilha *P1, *P2, *P3;

    int q;

    Inicializar_Pilha(&ini);

    do {
        system("cls");
        printf("PILHA\n");
        printf("\n\nOpcoes:\n");
        printf("1 -> Inserir\n");
        printf("2 -> Remover\n");
        printf("3 -> Inicializar\n");
        printf("4 -> Consultar Topo\n");
        printf("5 -> Verificar Vazio\n");
        printf("6 -> Listar\n");
        printf("9 -> Juntar Pilhas\n");
        printf("0 -> Sair\n\n:");
        scanf("%d", &q);

        switch(q) {
            case 9:
                Inicializar_Pilha(&P1);
                Inicializar_Pilha(&P2);

                Inserir_topo(&P1, 10);
                Inserir_topo(&P1, 20);
                Inserir_topo(&P1, 30);
                Inserir_topo(&P1, 40);

                Inserir_topo(&P2, 100);
                Inserir_topo(&P2, 200);
                Inserir_topo(&P2, 300);

                printf("\nP1:\n");
                Listar(P1);
                printf("\nP2:\n");
                Listar(P2);

                printf("\n--- Juntando ---\n");
                Juntar_pilhas(&P1, &P2, &P3);

                printf("\nP1 (apos):\n");
                Listar(P1);
                printf("\nP2 (apos):\n");
                Listar(P2);
                printf("\nP3 (resultado):\n");
                Listar(P3);

                system("pause");
                break;

            case 1:
                printf("Dado para insercao: ");
                scanf("%d", &info);
                erro = Inserir_topo(&ini, info);
                if (erro == 0)
                    printf("Insercao realizada com sucesso\n");
                system("pause");
                break;

            case 2:
                erro = Remover_topo(&ini);
                if (erro == 1)
                    printf("\nPilha vazia. Impossivel remover.\n");
                system("pause");
                break;

            case 3:
                Inicializar_Pilha(&ini);
                printf("\nPilha reinicializada!\n");
                system("pause");
                break;

            case 4:
                erro = Obter_topo(ini, &info);
                if (erro == 1)
                    printf("\nPilha vazia.\n");
                else
                    printf("\nTopo: %d\n", info);
                system("pause");
                break;

            case 5:
                Verifica_vazio(ini, &resposta);
                if (resposta == 1)
                    printf("\nPilha vazia\n");
                else
                    printf("\nPilha nao vazia\n");
                system("pause");
                break;

            case 6:
                Listar(ini);
                break;

            case 0:
                break;

            default:
                printf("\nOpcao invalida\n");
                system("pause");
        }

        getchar();
    } while (q != 0);

    return 0;
}

int Inicializar_Pilha(Tnode_pilha **inicio)
{
    // Falo que o topo da pilha esta nulo, sendo assim é uma pilha que ainda não recebeu nenhum dado.
    *inicio = NULL;
    return 0;
}

/// @brief Insere um novo valor no topo da pilha, estando ela vazia ou não.
/// @param inicio Ponteiro para a informação que atualmente está no topo da pilha.
/// @param novoDado Nova informação a ser inserida no topo.
/// @return O retorno é sempre 0 (Sucesso).
int Inserir_topo(Tnode_pilha **inicio, int novoDado)
{
    // Minha variavel posicaoNova é um novo nó que criei (nó = "objeto" de Tnode_pilha).
    Tnode_pilha *posicaoNova;
    posicaoNova = (Tnode_pilha *) malloc(sizeof(Tnode_pilha));
    
    posicaoNova -> dado = novoDado;

    // Caso não exista nada na pilha, eu digo que minha posicaoNova é o topo da minha pilha;
    if (*inicio == NULL)
    {
        posicaoNova -> prox = NULL;
        *inicio = posicaoNova;
    }
    else
    {
        // Caso a pilha não esteja vazia, eu vou primeiro apontar na posicao nova quem esta "embaixo" dela, que é o registro atual do topo.
        posicaoNova -> prox = *inicio;
        // Depois que criei o relacionamento entre a informação que chega e a que estava no topo, eu sobrescrevo a informação de quem é o topo da pilha.
        *inicio = posicaoNova;
    }

    return 0;    
}

/// @brief Remove a informação que está no topo da pilha e traz a informação que estava embaixo dela para o topo.
/// @param inicio Ponteiro para a informação que está no topo.
/// @return 1 - Quando a pilha esta vazia. | 0 - Sucesso.
int Remover_topo(Tnode_pilha **inicio)
{
    Tnode_pilha *aux;
    
    // Caso a pilha esteja vazia não é possível remover, então retorno um código de erro 1.
    if (*inicio == NULL)
        return 1;
    else
    {
        // Váriavel auxiliar que uso pra guardar o endereço de memoria que o inicio estava registrado, para que eu possa limpar ele depois de sobrescrever a variavel inicio.
        aux = *inicio;

        // Sobrescrevo inicio, falando que agora o topo da pilha é a informação que estava "embaixo" dessa que removi.
        *inicio = (*inicio) -> prox;

        // Limpo o endereço de memória que não uso mais.
        free(aux);

        // Retorno sucesso.
        return 0;
    }
    
}

/// @brief Atualiza a váriavel dado com o valor do Topo da pilha, 
/// @details Não retorna diretamente o valor, mas sim atribui o valor ao parâmetro por referência.
/// @param inicio Ponteiro para a informação no topo da pilha.
/// @param dado Ponteiro para o valor que está no topo da pilha.
/// @return 0 - Sucesso. | 1 - Quando a pilha está vazia.
int Obter_topo(Tnode_pilha *inicio, int *dado)
{
    if (inicio != NULL)
    {
        *dado = inicio -> dado;
        return 0;
    }
    else
        return 1; // Pilha vazia    
}

/// @brief Verifica se uma pilha está vazia.
/// @details Não retorna diretamente o valor, mas sim atribui o valor ao parâmetro por referência.
/// @param inicio Ponteiro para a informação no topo da pilha.
/// @param resp Ponteiro para a váriavel que contém a resposta se a pilha está ou não vazia.
/// @return Dentro de resp => 0 = não vazia. | 1 = vazia.
int Verifica_vazio(Tnode_pilha *inicio, int *resp)
{
    // Atribuo um valor para a variavel de resposta, não retornando diretamente o valor, mas atualizando a referência.
    if (!inicio == NULL)       
        *resp = 0;       
    else
       *resp = 1; 
    
    return 0; // Sucesso.
}

/// @brief Percorre a pilha, exibindo seus valores.
/// @param P1 Ponteiro para o topo da pilha.
/// @return Escreve na tela a pilha, do topo à base.
int Listar(Tnode_pilha *P1)
{
    printf("Pilha: ");

    // Enquanto eu não chegar a base da pilha, continuo exibindo as informações.
    while (P1 != NULL)
    {
        printf("%d - ", P1 -> dado);

        // A informação a ser exibida na proxima volta do While passa a ser a que estava embaixo da que foi exibida agora.
        P1 = P1 -> prox;
    }
    printf("\n");
    system("pause");
}

int Juntar_pilhas(Tnode_pilha **P1, Tnode_pilha **P2, Tnode_pilha **P3)
{
    Tnode_pilha *P_Aux;
    int resp, erro;
    int dado;

    // A pilha P3 é a pilha que vou obter depois de juntar P1 e P2.
    erro = Inicializar_Pilha(P3);
    // Inicializo a pilha P_Aux, passando um ponteiro de um ponteiro, que é &P_Aux, assim altero diretamente o endereço de memória daquela informação.
    erro = Inicializar_Pilha(&P_Aux);

    // Minha P3 recebe todo o conteudo de P2, ou seja, todos os nós encadeados a partir do topo de P2.
    *P3 = *P2;
    // Limpo a raiz de P2 porque ja tenho as informações dentro de P3.
    *P2 = NULL;

    Verifica_vazio(*P1, &resp);

    // Enquanto a pilha não estiver vazia, ou seja, enquanto não chegar no ultimo nó encadeado, o while continua rodando.
    while (resp == 0)
    {
        // Pego o topo da pilha P1, e atribuo para minha variavel interna dado.
        Obter_topo(*P1, &dado);
        // Tiro o dado que acabei de pegar do topo da pilha e puxo o que estava embaixo pra cima, assim quando o while passar de novo vai sobrescrever dado com o novo topo.
        Remover_topo(P1);
        // Começo a popular P_Aux, com P1 de "cabeça para baixo".
        Inserir_topo(&P_Aux, dado);
        // Verifico se meu while precisa passar novamente.
        Verifica_vazio(*P1, &resp);
    }

    Verifica_vazio(P_Aux, &resp);
    while (resp == 0)
    {
        // Vou fazer o mesmo processo do while anterior, porém, ao invés de tirar de P1 e colocar ao contrario em P_Aux,
        // irei tirar de P_Aux e colocar ao contrario em P3, de modo que volte a ordem original de P1.
        Obter_topo(P_Aux, &dado);
        Remover_topo(&P_Aux);
        Inserir_topo(P3, dado);
        Verifica_vazio(P_Aux, &resp);

    }
    

    return 0;
}