#ifndef _AUXILIAR_H_
#define _AUXILIAR_H_

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
using namespace std;

int dimensao = 0, veiculos, capacidade, qtdveiculos, seed = 0;
int *demanda;
int **nodes;
double **matriz;
double distancia_total = 0;

char pular_linha[] = "\n===================================================================================\n";

typedef struct
{
    vector<int> percurso;
    int carga;
    double distancia;
    int tamanho_percurso;

} rota_veiculo;

double **FazerMatriz(int **nodes)
{
    int num_linha = 0;
    double **matrix = (double**)malloc(sizeof(double*)*dimensao);
    double dx = 0, dy = 0, dist = 0;

    for (int i = 0; i < dimensao; i++)
    {
        matrix[num_linha++] = (double*)malloc(sizeof(double)*dimensao);
        for (int j = 0; j < dimensao; j++)
        {
            dx = (nodes[i][0] - nodes[j][0])*(nodes[i][0] - nodes[j][0]);
            dy = (nodes[i][1] - nodes[j][1])*(nodes[i][1] - nodes[j][1]);
            //printf("dx = %.2f --- dy = %.2f\n", dx, dy);

            dist = round(sqrt(dx + dy));           
            //printf("dist = %.2f\n", dist);
            matrix[i][j] = dist; 
            //printf("matrix[%d][%d] = %.2f\n", i, j, matrix[i][j]);
        }
    }

    return matrix;
}

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

int BuscaMenor(double **grafo, int cliente, bool *percorrido)
{
    //printf("Entrei com numcliente = %d\n", cliente);
    //printf("Entrei\n");
    int min = INT_MAX, min_index;
    for (int k = 0; k < dimensao; k++)
    {
        //printf("percorrido[%d] = %d --- grafo[%d][%d] = %.0f\n", k, percorrido[k], k, cliente, grafo[k][cliente]);
        //printf("percorrido[k] = %d --- min = %d --- min_index = %d\n", percorrido[k], min, min_index);
        if (percorrido[k] == false && grafo[k][cliente] < min)
        {
            min = grafo[k][cliente];
            min_index = k;
        }
    }

    /*int min = INT_MAX, min_index;  
  
    for (int k = 0; k < dimensao; k++)  
    {
        printf("Percorrido: %b --- chave: %d --- min: %d --- min_index: %d\n", percorrido[k], chave[k], min, min_index);
        if (percorrido[k] == false && chave[k] < min)  
            min = chave[k], min_index = k;
    } */
    //printf("Terminei com c = %d\n", min_index);
    return min_index;
}

void Print_Percurso(vector<int> percurso, int dist)
{
    int i, count = 0;
    for (i = 0; i < dist; i++)
    {
        count++;
        if (i == dist - 1)
            printf("%d;\n", percurso[i]);
        
        else
            printf("%d, ", percurso[i]);
    }
    //printf("%d nos visitados\n", count);
}

int Distancia(int *percurso, double **grafo, int dist)
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