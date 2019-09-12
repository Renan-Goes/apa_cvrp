#ifndef __CONSTRUCAO_H_
#define __CONSTRUCAO_H_

#include "auxiliar.h"


int minKey(int key[], bool mstSet[])  
{  
    // Valor minimo inicial tem que ser o maior possivel
    int min = 2147483647, min_index;  
  
    for (int v = 0; v < dimensao; v++)  
        if (mstSet[v] == false && key[v] < min)  
            min = key[v], min_index = v; 
  
    return min_index;
}

struct rota_veiculo *Guloso(int **grafo)
{
    int distancia = 0, count = 0, count2, cidade = 0;
    struct rota_veiculo *solucao = (struct rota_veiculo*)malloc(sizeof(struct rota_veiculo)*veiculos);
    size_t sz = 0;
    int* clientes_atendidos = (int*)malloc(sizeof(int)*dimensao);
    clientes_atendidos[0] = 0;
    int indice_clientes = 1;
    for (int l = 1; l < dimensao; l++)
        clientes_atendidos[l] = -1;

    while (count < veiculos)
    {
        int *solucao_rota = (int*)malloc(sizeof(int)*dimensao);

        for (int e = 0; e < dimensao; e++)
            solucao_rota[e] = -1;

        *solucao_rota = 0;
        solucao[count].carga = demanda[0];
        solucao[count].distancia = 0;
        solucao[count].tamanho_percurso = 1;
        count2 = 1;
        //Print_Percurso(clientes_atendidos, dimensao);

        while (solucao[count].carga < capacidade)
        {
            if (indice_clientes == dimensao)
            {
                
                solucao_rota[count2] = 0;
                solucao[count].distancia += grafo[solucao_rota[count2 - 1]][solucao_rota[count2]];
                solucao[count].carga += demanda[solucao_rota[count2]];
                solucao[count].tamanho_percurso++;

                solucao[count].percurso = solucao_rota;
                free(solucao_rota);
                Print_Percurso(clientes_atendidos, dimensao);

                printf("Acabou!\n");

                return solucao;
            }

            solucao_rota[count2] = rand() % dimensao;

            while(Visitado(clientes_atendidos, solucao_rota[count2], dimensao))
            {
                solucao_rota[count2] = rand() % dimensao;
                //printf("Visitado: %d, cliente: %d\n", Visitado(clientes_atendidos, solucao_rota[count2], dimensao), solucao_rota[count2]);
            }
            clientes_atendidos[indice_clientes++] = solucao_rota[count2];

            solucao[count].distancia += grafo[solucao_rota[count2 - 1]][solucao_rota[count2]];
            solucao[count].carga += demanda[solucao_rota[count2]];
            solucao[count].tamanho_percurso++;
            count2++;
        }

        solucao_rota[count2] = 0;
        solucao[count].distancia += grafo[solucao_rota[count2 - 1]][solucao_rota[count2]];
        solucao[count].carga += demanda[solucao_rota[count2]];
        solucao[count].tamanho_percurso++;

        
        Print_Percurso(solucao_rota, dimensao);
        solucao[count].percurso = solucao_rota;
        Print_Percurso(solucao[count].percurso, dimensao);
        puts(pular_linha);
        //free(solucao_rota);

        /*if (solucao[count].percurso[solucao[count].tamanho_percurso - 2] == 0)
        {
            solucao[count].tamanho_percurso--;
            solucao[count].carga -= demanda[0];
        }*/

        count++;
    }

    //return solucao;
}

/*int *primMST(int **grafo)  
{  
    int indice_percurso = 0;
    int *percurso;
    percurso = (int*)malloc(sizeof(int)*(dimensao));
      
    int key[dimensao];  
      
    bool mstSet[dimensao];
  
    for (int i = 0; i < dimensao; i++)  
        key[i] = 2147483647, mstSet[i] = false;  
  
    key[0] = 0;  
  
    for (int count = 0; count < dimensao - 1; count++) 
    {  
        int u = minKey(key, mstSet);
  
        mstSet[u] = true;  
        percurso[indice_percurso] = u;
        //printf("%d\n", percurso[indice_percurso]);
        indice_percurso++;
  
        for (int v = 0; v < dimensao; v++)   
            if (grafo[u][v] && mstSet[v] == false && grafo[u][v] < key[v])  
                key[v] = grafo[u][v];  
    }

    //percurso[indice_percurso] = percurso[0];
  
    //printMST(pais, grafo);  
    return percurso;
}*/

#endif