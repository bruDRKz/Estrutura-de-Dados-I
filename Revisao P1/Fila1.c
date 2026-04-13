#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Defino o tamanho estatico da minha fila.
#define tamanho 5


typedef struct Fila{
    int item[tamanho];
    int inicio, fim;
} T_Fila;


/// @brief Inicializa a Fila com valores -1, o que significa que a fila está vazia.
/// @param fila 
/// @return 0 - Sucesso;
int InicializaFila(T_Fila *fila)
{
    fila -> inicio = -1;
    fila -> fim = -1;

    return 0;
}

/// @brief Verifica o estado da fila, se está cheia, vazia, ou preenchida mas com posições disponiveis.
/// @param fila 
/// @return 0 - Fila vazia. | 1 - Fila cheia. | 2 - Preenchida, porém com espaços disponiveis.
int VerificaEstado(T_Fila fila)
{
    if ((fila.inicio == -1) || (fila.inicio == tamanho) || (fila.inicio == fila.fim+1))
        return 0; // Fila vazia

    else
    {
        if (fila.fim == tamanho -1)
            return 1; // Fila cheia
        else
            return 2; // Fila não vazia, porém com espaço disponivel.
    }
}

/// @brief Insere um novo valor no fim da fila, de acordo com a possibilidade de inserção da fila em relação ao estado dela.
/// @param fila 
/// @param valor 
/// @return 0 - Sucesso. | 1 - Overflow/Fila cheia.
int InsereFimDaFila(T_Fila *fila, int valor)
{
    int estadoFila = VerificaEstado(*fila);
    if ((estadoFila == 0) || (estadoFila == 2))
    {
        fila -> fim ++;
        fila -> item[fila -> fim] = valor;

        if (fila -> inicio == -1)
            fila -> inicio = 0;
        
        return 0; 
    }
    
    else 
        return 1; // Fila cheia, não é possível inserir novos valores.  
}

/// @brief Caso a fila não seja vazia, removo o item que esta na primeira posição e o item seguinte assume esse indice.
/// @param fila 
/// @return 0 - Sucesso. | 1 - Underflow, a fila ja está vazia.
int RemovePrimeiroDaFila(T_Fila *fila)
{
    int estadoFila = VerificaEstado(*fila);

    if (estadoFila != 0)
    {
        // A fila "anda" e o primeiro da fila passa a ser o item seguinte ao "removido".
        fila -> inicio ++;
        if (fila -> inicio > fila -> fim)
        {
            // Se eu removi o ultimo valor da fila, eu posso resetar a contagem dela e dizer que ela está vazia e pode ser preenchida de novo.
            fila -> fim = -1;
            fila -> inicio = -1;
        }
        
        return 0;
    }
    else 
        return 1; // Impossível remover, a fila ja está vazia.    
}

/// @brief Caso a fila não seja vazia, percorro todos os indices exibindo os valores dispostos em cada um.
/// @param fila 
/// @return 0 - Sucesso | 1 - Fila vazia, impossível listar.
int ListarItens(T_Fila fila)
{
    int estadoFila, i;
    estadoFila = VerificaEstado(fila);

    if (estadoFila != 0)
    {
        for (i = fila.inicio; i<= fila.fim; i++)
            printf("%d - ", fila.item[i]);            

        printf("\n");

        return 0;                  
    }
    else return 1; // A fila está vazia, não é possível listar.    
}

/// @brief Caso a fila não seja vazia, devolvo o valor que está inserido dentro da primeira posição da fila, no indice que esta armazenado em inicio;
/// @param fila 
/// @param dado 
/// @return 0 - Sucesso. | 1 - Fila vazia.
int ObterPrimeiroDaFila(T_Fila fila, int *dado)
{
    int estadoFila = VerificaEstado(fila);

    // Caso a fila não seja vazia, eu retorno o valor contido no indice que esta na posição inicio.
    if (estadoFila != 0 )
    {
        *dado = fila.item[fila.inicio];
        return 0;
    }

    else 
        return 1; // Fila vazia.
}

int main(void)
{
    int info;
    int erro; 
    T_Fila fila;

    int opcao;

    do {
        system("cls"); 
        printf("FILA Estatica\n");
        printf("\nOpcoes:\n\n");
        printf("1 -> Inicializar Fila\n");
        printf("2 -> Inserir elemento\n");
        printf("3 -> Remover elemento\n");
        printf("4 -> Verificar estado\n");
        printf("5 -> Listar elementos\n");
        printf("6 -> Obter primeiro elemento\n");
        printf("7 -> Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                erro = InicializaFila(&fila);
                printf("\nFila inicializada com sucesso!\n");
                system("pause");
                break;

            case 2:
                printf("Digite o valor: ");
                scanf("%d", &info);
                erro = InsereFimDaFila(&fila, info);

                if (erro == 1)
                    printf("\nFila cheia (Overflow)\n");

                system("pause");
                break;

            case 3:
                erro = RemovePrimeiroDaFila(&fila);

                if (erro == 1)
                    printf("\nFila vazia (Underflow)\n");
                else
                    printf("\nElemento removido com sucesso!\n");

                system("pause");
                break;

            case 4:
                erro = VerificaEstado(fila);

                if (erro == 0)
                    printf("\nFila vazia\n");
                else if (erro == 1)
                    printf("\nFila cheia\n");
                else
                    printf("\nFila com espaco disponivel\n");

                system("pause");
                break;

            case 5:
                erro = ListarItens(fila);

                if (erro == 1)
                    printf("\nFila vazia\n");

                system("pause");
                break;

            case 6:
                erro = ObterPrimeiroDaFila(fila, &info);

                if (erro == 0)
                    printf("\nPrimeiro elemento: %d\n", info);
                else
                    printf("\nFila vazia\n");

                system("pause");
                break;

            case 7:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                system("pause");
        }

    } while (opcao != 7);

    return 0;
}