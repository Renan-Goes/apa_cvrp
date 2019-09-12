#ifndef _AUXILIAR_H_
#define _AUXILIAR_H_

#include <time.h>
#include <stdlib.h>

int dimensao = 0, veiculos, capacidade;
int *demanda;

char pular_linha[] = "\n===================================================================================\n";

struct rota_veiculo
{
    int *percurso;
    int carga;
    int distancia;
    int tamanho_percurso;
};

/*int Maior_Demanda(struct rota_veiculo rota)
{
    int maior = 0, i;
    for (i = 0; i < dimensao; i++)
    {
        if (!Visitado(rota.percurso, i, rota.tamanho_percurso) && demanda[i] > maior)
            maior = demanda[i];
    }

    return i;
}*/

void Print_Percurso(int *percurso, int dist)
{
    int i, count = 0;
    for (i = 0; i < dist; i++)
    {
        count++;
        if (i == dist - 1)
            printf("%d\n", percurso[i]);
        
        else
            printf("%d -> ", percurso[i]);
    }
    printf("%d nos visitados\n", count);
}

int Distancia(int *percurso, int **grafo, int dist)
{
    int total = 0;
    for (int i = 0; i < dist - 1; i++)
    {
        total += grafo[percurso[i]][percurso[i + 1]];
    }

    return total;
}

bool Visitado(int *percurso, int v, int indice)
{
    for (int x = 0; x < indice; x++)
    {
        if (percurso[x] == v)
            return 1;
    }
    
    return 0;
}

bool Verifica_Visitado(int *percurso)
{
    for (int i = 1; i < dimensao; i++)
    {
        for (int j = i + 1; j < dimensao; j++)
        {
            if (percurso[i] == percurso[j])
            {
                printf("Percurso[%d] = %d e Percurso[%d] = %d !!!\n", i, percurso[i], j, percurso[j]);
                return 1;
            }
        }
    }

    printf("Tudo normal! :)\n");
    puts(pular_linha + '\n');

    return 0;
}

#endif