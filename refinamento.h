#ifndef __REFINAMENTO_H_
#define __REFINAMENTO_H_

#include "auxiliar.h"

bool Contem_Ou_Nao(int *percurso, int partida, int chegada)
{
    bool contem = 0;
    int i;

    for (i = 1; i < dimensao - 1; i++)
    {
        contem = (percurso[i] == chegada && percurso[i + 1] == partida) || (percurso[i + 1] == chegada && percurso[i] == partida);
        if (contem)
            return 1;
    }

    return contem;
}

int Menor_Aresta(int **grafo, int *percurso, int vertice)
{
    int distancia_minima = 0;
    int aresta_proxima;

    for (int i = 0; i < dimensao; i++)
    {
        if(!Contem_Ou_Nao(percurso, i, vertice) && (distancia_minima == 0 || grafo[i][vertice] < distancia_minima) && i != vertice)
        {
            distancia_minima = grafo[i][vertice];
            aresta_proxima = i;
        }
    }
    return aresta_proxima;
}

struct rota_veiculo *SWAP(int **grafo, struct rota_veiculo *nova_rota)
{    
    int aux, distancia_anterior = 0;
    for (int i = 0; i < veiculos; i++)
    {
        if(nova_rota[i].percurso != NULL)
        {
            distancia_anterior = nova_rota[i].distancia;
            Print_Percurso(nova_rota[i].percurso, nova_rota[i].tamanho_percurso);
            printf("Distancia anterior: %d, ", distancia_anterior);
            //aux = 0;
            int cliente1 = (rand() % (nova_rota[i].tamanho_percurso - 2)) + 1, cliente2 = (rand() % (nova_rota[i].tamanho_percurso - 2)) + 1;

            while(cliente1 == cliente2)
                cliente2 = (rand() % (nova_rota[i].tamanho_percurso - 2)) + 1;

            //printf("\n\nCliente1: %d --- Cliente2: %d\n", cliente1, cliente2);
            //Print_Percurso(nova_rota[i].percurso, nova_rota[i].tamanho_percurso);

            aux = nova_rota[i].percurso[cliente2];
            nova_rota[i].percurso[cliente2] = nova_rota[i].percurso[cliente1];
            nova_rota[i].percurso[cliente1] = aux;
            
            nova_rota[i].distancia = nova_rota[i].distancia 
            - grafo[nova_rota[i].percurso[cliente1]][nova_rota[i].percurso[cliente2 - 1]] 
            - grafo[nova_rota[i].percurso[cliente1]][nova_rota[i].percurso[cliente2 + 1]] 
            - grafo[nova_rota[i].percurso[cliente2]][nova_rota[i].percurso[cliente1 - 1]] 
            - grafo[nova_rota[i].percurso[cliente2]][nova_rota[i].percurso[cliente1 + 1]] 
            + grafo[nova_rota[i].percurso[cliente1]][nova_rota[i].percurso[cliente1 - 1]] 
            + grafo[nova_rota[i].percurso[cliente1]][nova_rota[i].percurso[cliente1 + 1]]
            + grafo[nova_rota[i].percurso[cliente2]][nova_rota[i].percurso[cliente2 - 1]] 
            + grafo[nova_rota[i].percurso[cliente2]][nova_rota[i].percurso[cliente2 + 1]];

            //Print_Percurso(nova_rota[i].percurso, nova_rota[i].tamanho_percurso);

            printf("Distancia calculada: %d, distancia verdadeira: %d\n", nova_rota[i].distancia, Distancia(nova_rota[i].percurso, grafo, nova_rota[i].tamanho_percurso));

            if (nova_rota[i].distancia > distancia_anterior)
            {
                aux = nova_rota[i].percurso[cliente1];
                nova_rota[i].percurso[cliente1] = nova_rota[i].percurso[cliente2];
                nova_rota[i].percurso[cliente2] = aux;
                nova_rota[i].distancia = distancia_anterior;
            }
        }    
    }

    return nova_rota;
}

struct rota_veiculo *Dois_OPT(int **grafo, struct rota_veiculo *nova_rota)
{    
    int aux, aux2, distancia_anterior = 0;
    for (int i = 0; i < veiculos; i++)
    {
        if(nova_rota[i].percurso != NULL && nova_rota[i].tamanho_percurso >= 6)
        {
            distancia_anterior = nova_rota[i].distancia;
            Print_Percurso(nova_rota[i].percurso, nova_rota[i].tamanho_percurso);
            //aux = 0;
            int cliente1 = (rand() % (nova_rota[i].tamanho_percurso - 3)) + 1, cliente2 = (rand() % (nova_rota[i].tamanho_percurso - 3)) + 1;

            while(cliente1 == cliente2 || cliente2 == cliente1 - 1 || cliente2 == cliente1 + 1)
                cliente2 = (rand() % (nova_rota[i].tamanho_percurso - 3)) + 1;
            
            printf("Cliente1: (indice:%d, cliente: %d), Cliente1 + 1: (indice:%d, cliente: %d), Cliente2: (indice:%d, cliente: %d), "
            "Cliente2 + 1: (indice:%d, cliente: %d)\nDistancia anterior: %d, ", cliente1, nova_rota[i].percurso[cliente1], cliente1 + 1, nova_rota[i].percurso[cliente1 + 1], cliente2, nova_rota[i].percurso[cliente2], cliente2 + 1, nova_rota[i].percurso[cliente2 + 1], distancia_anterior);
            
            //printf("\n\nCliente1: %d --- Cliente2: %d\n", cliente1, cliente2);
            //Print_Percurso(nova_rota[i].percurso, nova_rota[i].tamanho_percurso);
            
            nova_rota[i].distancia = nova_rota[i].distancia
            - grafo[nova_rota[i].percurso[cliente1]][nova_rota[i].percurso[cliente1 - 1]]
            - grafo[nova_rota[i].percurso[cliente1]][nova_rota[i].percurso[cliente1 + 1]]
            - grafo[nova_rota[i].percurso[cliente1 + 1]][nova_rota[i].percurso[cliente1 + 2]]
            - grafo[nova_rota[i].percurso[cliente2]][nova_rota[i].percurso[cliente2 - 1]]
            - grafo[nova_rota[i].percurso[cliente2]][nova_rota[i].percurso[cliente2 + 1]]
            - grafo[nova_rota[i].percurso[cliente2 + 1]][nova_rota[i].percurso[cliente2 + 2]]
            + grafo[nova_rota[i].percurso[cliente1 + 1]][nova_rota[i].percurso[cliente2 - 1]]
            + grafo[nova_rota[i].percurso[cliente1 + 1]][nova_rota[i].percurso[cliente1]]
            + grafo[nova_rota[i].percurso[cliente1]][nova_rota[i].percurso[cliente2 + 2]]
            + grafo[nova_rota[i].percurso[cliente2 + 1]][nova_rota[i].percurso[cliente1 - 1]]
            + grafo[nova_rota[i].percurso[cliente2 + 1]][nova_rota[i].percurso[cliente2]]
            + grafo[nova_rota[i].percurso[cliente2]][nova_rota[i].percurso[cliente1 + 2]];

            aux = nova_rota[i].percurso[cliente2];
            aux2 = nova_rota[i].percurso[cliente2 + 1];
            nova_rota[i].percurso[cliente2 + 1] = nova_rota[i].percurso[cliente1];
            nova_rota[i].percurso[cliente2] = nova_rota[i].percurso[cliente1 + 1];
            nova_rota[i].percurso[cliente1 + 1] = aux;
            nova_rota[i].percurso[cliente1] = aux2;

            //Print_Percurso(nova_rota[i].percurso, nova_rota[i].tamanho_percurso);

            printf("Distancia calculada: %d, distancia verdadeira: %d\n", nova_rota[i].distancia, Distancia(nova_rota[i].percurso, grafo, nova_rota[i].tamanho_percurso));

            if (nova_rota[i].distancia > distancia_anterior)
            {
                aux = nova_rota[i].percurso[cliente1];
                nova_rota[i].percurso[cliente1] = nova_rota[i].percurso[cliente2];
                nova_rota[i].percurso[cliente2] = aux;
                nova_rota[i].distancia = distancia_anterior;
            }
        }    
    }

    return nova_rota;
}

/*struct rota_veiculo *VNN(int **grafo, struct rota_veiculo *nova_rota)
{
    int indice, distancia_atual = Distancia(percurso, grafo), aux = percurso[1];
    int nova_distancia = distancia_atual;
    int distancia_aux = nova_distancia;

    int *percurso_final = (int*)malloc(sizeof(int)*dimensao);
    for (int i = 0; i < dimensao; i++)
    {
        percurso_final[i] = percurso[i];
    }


    for (int indice = 0; indice < dimensao; indice++)
    {
        int aresta = Menor_Aresta(grafo, percurso, percurso[indice]);
        int *percurso_aux = (int*)malloc(sizeof(int)*dimensao);
        if (!Visitado(percurso, percurso[aresta], indice))
        {
            for (int j = 0; j < dimensao; j++)
            {
                percurso_aux[j] = percurso[j];
            }
            aux = percurso_aux[indice + 1];
            percurso_aux[indice + 1] = percurso_aux[aresta];
            percurso_aux[aresta] = aux;

            distancia_aux = Distancia(percurso_aux, grafo);
            
            if (distancia_aux < nova_distancia)
            {
                nova_distancia = distancia_aux;
                percurso = percurso_aux;
                printf("Nova solucao encontrada!\n");
                printf("Solucao encontrada:\n");
                Print_Percurso(percurso_aux, dimensao);
                printf("Distancia calculada: %d\n", Distancia(percurso, grafo));
                free(percurso_aux);
                return percurso;
            }
            else
            {
                free(percurso_aux);
            }
        }
    }
    return percurso_final;
}*/

/*int *VND(int **grafo, int *percurso, int iteracoes)
{
    int dist = Distancia(percurso, grafo);
    for (int i = 0; i < iteracoes; i++)
    {
        percurso = Vizinho_Mais_Proximo(grafo, percurso);         
    }


    return percurso;
}*/

#endif