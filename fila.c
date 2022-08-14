
// PROGRAMA DESENVOLVIDO PELA DUPLA:  GEANDERSON LEMONTE E LUIZ FERNANDO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 10

typedef char string[20];

typedef struct elemento
{
    int prioridade;
    string nome;
} TElemento;

int opcoes()
{
    int entrada = 0;
    printf("Escolha uma opcao no meu : \n ");
    printf("    0 - Sair : \n ");
    printf("    1 - Inserir na fila : \n ");
    printf("    2 - Remover da fila : \n ");
    printf("    3 - Exibir fila : \n ");
    printf("    4 - Exibir os próximos 6 elementos a serem atendidos : \n ");
    scanf("%d", &entrada);
    return entrada;
}

TElemento inserirDados()
{
    TElemento elemento;
    printf("Insira o nome do elemento: ");
    scanf("%s", elemento.nome);
    do
    {
        printf("Insira a prioridade do elemento (1, 2, 3) : ");
        scanf("%d", &elemento.prioridade);
    } while (elemento.prioridade > 3 || elemento.prioridade < 0);
    return elemento;
}

TElemento elementoNulo()
{
    TElemento elemento;
    elemento.prioridade = 0;
    return elemento;
}
void resetarVetor(TElemento elemento[])
{
    int i = 0;
    for (i = 0; i < TAMANHO; i++)
    {
        elemento[i] = elementoNulo();
    }
}

void reorganizaVetor(TElemento elemento[])
{
    int i = 0;
    for (i = 0; i < (TAMANHO - 1); i++)
    {
        if (elemento[i].prioridade == 0 && elemento[i + 1].prioridade != 0)
        {
            elemento[i] = elemento[i + 1];
            elemento[i + 1] = elementoNulo();
        }
    }
}

void mostrarVetor(TElemento elemento[])
{
    int i = 0;
    for (i = 0; i < TAMANHO; i++)
    {
        if (elemento[i].prioridade != 0)
        {
            printf("%s ", elemento[i].nome);
            printf("------- %d ", elemento[i].prioridade);
            printf("\n\n");
        }
    }
}

void resetaPesos(int *pesos)
{
    pesos[0] = 2;
    pesos[1] = 1;
    pesos[2] = 3;
}

int calculaPeso(int pesos[])
{
    int peso = -1;
    if (pesos[0] == 0 && pesos[1] == 0 && pesos[2] == 0)
    {
        resetaPesos(pesos);
    }
    if (pesos[2] > 0)
    {
        peso = 3;
        pesos[2] = pesos[2] - 1;
    }
    else
    {
        if (pesos[0] > 0)
        {
            peso = 1;
            pesos[0] = pesos[0] - 1;
        }
        else
        {
            if (pesos[1] > 0)
            {
                peso = 2;
                pesos[1] = pesos[1] - 1;
            }
        }
    }
    return peso;
}

int removerElementoFila(TElemento elemento[], int pesos[])
{

    int posicaoRemover = -2, i;
    int peso = calculaPeso(pesos);
    while (posicaoRemover == -2)
    {
        for (i = 0; i < TAMANHO; i++)
        {
            if (elemento[i].prioridade == peso)
            {
                posicaoRemover = i;
                elemento[i] = elementoNulo();
                return posicaoRemover;
            }
        }
        if (posicaoRemover == -2)
        {
            switch (peso)
            {
            case 1:
                peso = 2;
                break;
            case 3:
                peso = 1;
                break;
            default:
                posicaoRemover = -1;
                return posicaoRemover;
                break;
            }
        }
    }
    return posicaoRemover;
}

void ordenarElementosEmOrdemDeRetirada(TElemento elemento[], int pesos[])
{
    TElemento elementosEmOrdemDeRetirada[TAMANHO];
    TElemento listaAux[TAMANHO];
    resetarVetor(elementosEmOrdemDeRetirada);
    int tamanhoVetorRetirada = -1;
    int i =0;
    for(i =0; i< TAMANHO; i ++){
        listaAux[i] = elemento[i];
    }
    for(i = 0; i <6; i ++){
       int pos = removerElementoFila(listaAux, pesos);
       if(pos > -1) {
           tamanhoVetorRetirada = tamanhoVetorRetirada +1;
           elementosEmOrdemDeRetirada[tamanhoVetorRetirada] = elemento[pos];
       }
    }
    mostrarVetor(elementosEmOrdemDeRetirada);
}


void menu()
{
    int enquanto = -1;
    TElemento elemento[TAMANHO];
    int posicaoRemovida = -1;
    int ultimaPosicaoVetor = -1;
    int pesos[3];
    resetarVetor(elemento);
    resetaPesos(pesos);
    do
    {
        enquanto = opcoes();
        switch (enquanto)
        {
        case 0:
            printf("O programa esta sendo finalizado! \n");
            break;
        case 1:
            if (ultimaPosicaoVetor == 19)
            {
                printf("\n ---- O fila está cheia ---- \n");
            }
            else
            {
                elemento[ultimaPosicaoVetor + 1] = inserirDados();
                ultimaPosicaoVetor = ultimaPosicaoVetor + 1;
            }
            break;
        case 2:
            if (ultimaPosicaoVetor > -1)
            {
                posicaoRemovida = removerElementoFila(elemento, pesos);
                if (posicaoRemovida != -1)
                {
                    reorganizaVetor(elemento);
                    ultimaPosicaoVetor = ultimaPosicaoVetor - 1;
                }
            }
            else
            {
                printf("\n ---- A fila está vazia ---- \n");
            }
            break;
        case 3:
            if (ultimaPosicaoVetor > -1)
            {
                mostrarVetor(elemento);
            }
            else
            {
                printf("\n ---- A fila está vazia ---- \n");
            }
            break;
        case 4:
            if (ultimaPosicaoVetor > -1)
            {
                ordenarElementosEmOrdemDeRetirada(elemento, pesos);
            }
            else
            {
                printf("\n ---- A fila está vazia ---- \n");
            }
            break;
        default:
            printf("Insira um valor de 0 a 4 \n");
            break;
        }
    } while (enquanto != 0);
}

int main()
{
    menu();
    return 0;
}