#ifndef __REFINAMENTO_H_
#define __REFINAMENTO_H_

#include "auxiliar.h"

vector<rota_veiculo> SWAP(double **grafo, vector<rota_veiculo> rota)
{
    int aux, distancia_anterior = 0;
    vector<rota_veiculo> rota_swap;

    for(int i = 0; i <= qtdveiculos; i++)
    {
        rota_swap.push_back(rota_veiculo());
        //printf("\nVeiculo %d\n", i);
        //rota_swap[i].percurso = (int*)realloc(rota[i].percurso, sizeof(int)*dimensao);
        //rota_swap[i].percurso.push_back(int());
        
        rota_swap[i].carga = rota[i].carga;
        rota_swap[i].tamanho_percurso = rota[i].tamanho_percurso;
        distancia_anterior = rota[i].distancia;
        rota_swap[i].distancia = distancia_anterior;

        for (int o = 0; o < rota[i].tamanho_percurso; o++)
        {
            rota_swap[i].percurso.push_back(int());
            rota_swap[i].percurso[o] = rota[i].percurso[o];
        }

        srand(time(0));
        seed = rand() % 10000;
        srand(seed);
        seed += 3;
        double adj[] = {0.4, 0.5, 0.6, 0.7, 0.8};
        int a = sizeof(adj) / sizeof(*adj);
        double swap_ajuste = 0;
        int ajuste = 0;

        if (rota_swap[i].tamanho_percurso >= 4)
        {
            swap_ajuste = adj[rand() % a];
            ajuste = int(round((swap_ajuste * rota_swap[i].tamanho_percurso)));

            int *rota_aux = (int*)malloc(sizeof(int)*dimensao);
            for (int m = 0; m < rota[i].tamanho_percurso; m++)
            {
                rota_aux[m] = rota[i].percurso[m];
            }

            for (int j = 1; j < ajuste; j = j + 2)
            {
                //printf("rota_swap[i].percurso[j] = %d\n", rota[i].percurso[j]);
                rota_swap[i].distancia = rota_swap[i].distancia
                - grafo[rota[i].percurso[j]][rota[i].percurso[j - 1]]
                - grafo[rota[i].percurso[j + 1]][rota[i].percurso[j + 2]]
                + grafo[rota[i].percurso[j + 1]][rota[i].percurso[j - 1]]
                + grafo[rota[i].percurso[j]][rota[i].percurso[j + 2]];


                //printf("Antes: %d -> %d, ", rota[i].percurso[j], rota[i].percurso[j + 1]);
                aux = rota[i].percurso[j];
                rota_swap[i].percurso[j] = rota[i].percurso[j + 1];
                rota_swap[i].percurso[j + 1] = aux;
                //printf("Depois: %d -> %d\n", rota_swap[i].percurso[j], rota_swap[i].percurso[j + 1]);

                if (rota_swap[i].distancia > distancia_anterior)
                {
                    rota_swap[i].percurso = rota[i].percurso;
                    // for (int k = 0; k < rota_swap[i].tamanho_percurso; k++)
                    // {
                    //     rota_swap[i].percurso[k] = rota_aux[k];
                    // }
                    // rota_swap[i].distancia = distancia_anterior;
                }
            }
            free(rota_aux);
        }
        //Print_Percurso(rota_swap[i].percurso, rota_swap[i].tamanho_percurso);
    }

    return rota_swap;    
}


vector<rota_veiculo> DoitOPT(double **grafo, vector<rota_veiculo> rota)
{
    int aux, aux2, distancia_anterior = 0;
    vector<rota_veiculo> rota_DoisOPT;

    for(int i = 0; i <= qtdveiculos; i++)
    {
        rota_DoisOPT.push_back(rota_veiculo());
        //printf("\nVeiculo %d\n", i);
        //rota_DoisOPT[i].percurso = (int*)realloc(rota[i].percurso, sizeof(int)*dimensao);
        rota_DoisOPT[i].carga = rota[i].carga;
        rota_DoisOPT[i].tamanho_percurso = rota[i].tamanho_percurso;
        distancia_anterior = rota[i].distancia;
        rota_DoisOPT[i].distancia = distancia_anterior;


        srand(time(0));
        seed = rand() % 10000;
        srand(seed);
        seed += 3;
        double adj[] = {0.4, 0.5, 0.6, 0.7, 0.8};
        int a = sizeof(adj) / sizeof(*adj);
        double swap_ajuste = 0;
        int ajuste = 0;
        
        for (int o = 0; o < rota[i].tamanho_percurso; o++)
        {
            rota_DoisOPT[i].percurso.push_back(int());
            rota_DoisOPT[i].percurso[o] = rota[i].percurso[o];
        }

        if (rota_DoisOPT[i].tamanho_percurso >= 4)
        {
            swap_ajuste = adj[rand() % a];
            ajuste = int(round((swap_ajuste * rota_DoisOPT[i].tamanho_percurso)));

            int *rota_aux = (int*)malloc(sizeof(int)*dimensao);
            for (int m = 0; m < rota[i].tamanho_percurso; m++)
            {
                rota_aux[m] = rota[i].percurso[m];
            }

            for (int j = 1; j < ajuste && j < rota[i].tamanho_percurso - 5; j = j + 3)
            {   
                rota_DoisOPT[i].distancia = rota_DoisOPT[i].distancia
                - grafo[rota[i].percurso[j]][rota[i].percurso[j - 1]]
                - grafo[rota[i].percurso[j + 3]][rota[i].percurso[j + 4]]
                + grafo[rota[i].percurso[j + 3]][rota[i].percurso[j - 1]]
                + grafo[rota[i].percurso[j]][rota[i].percurso[j + 4]];


                //printf("Antes: %d -> %d, ", rota[i].percurso[j], rota[i].percurso[j + 1]);
                aux = rota[i].percurso[j];
                rota_DoisOPT[i].percurso[j] = rota[i].percurso[j + 1];
                rota_DoisOPT[i].percurso[j + 1] = aux;
                //printf("Depois: %d -> %d\n", rota_DoisOPT[i].percurso[j], rota_DoisOPT[i].percurso[j + 1]);

                if (rota_DoisOPT[i].distancia > distancia_anterior)
                {
                    rota_DoisOPT[i].percurso = rota[i].percurso;
                    // for (int k = 0; k < rota_DoisOPT[i].tamanho_percurso; k++)
                    // {
                    //     rota_DoisOPT[i].percurso[k] = rota_aux[k];
                    // }
                    // rota_DoisOPT[i].distancia = distancia_anterior;
                }
            }
            free(rota_aux);
        }
        //Print_Percurso(rota_DoisOPT[i].percurso, rota_DoisOPT[i].tamanho_percurso);
    }

    return rota_DoisOPT;  


}

vector<rota_veiculo> Inverter(double **grafo, vector<rota_veiculo> rota)
{
    int aux, distancia_anterior = 0;
    vector<rota_veiculo> rota_inverter;

    for(int i = 0; i <= qtdveiculos; i++)
    {
        rota_inverter.push_back(rota_veiculo());
        //printf("\nVeiculo %d\n", i);
        //rota_inverter[i].percurso = (int*)realloc(rota[i].percurso, sizeof(int)*dimensao);
        rota_inverter[i].carga = rota[i].carga;
        rota_inverter[i].tamanho_percurso = rota[i].tamanho_percurso;
        distancia_anterior = rota[i].distancia;
        rota_inverter[i].distancia = distancia_anterior;


        srand(time(0));
        seed = rand() % 10000;
        srand(seed);
        seed += 3;
        double adj[] = {0.4, 0.5, 0.6, 0.7, 0.8};
        int a = sizeof(adj) / sizeof(*adj);
        double swap_ajuste = 0;
        int ajuste = 0;
        
        for (int o = 0; o < rota[i].tamanho_percurso; o++)
        {
            rota_inverter[i].percurso.push_back(int());
            rota_inverter[i].percurso[o] = rota[i].percurso[o];
        }

        if (rota_inverter[i].tamanho_percurso >= 4)
        {
            swap_ajuste = adj[rand() % a];
            ajuste = int(round((swap_ajuste * rota_inverter[i].tamanho_percurso)));

            int *rota_aux = (int*)malloc(sizeof(int)*dimensao);
            for (int m = 0; m < rota[i].tamanho_percurso; m++)
            {
                rota_aux[m] = rota[i].percurso[m];
            }

            int aux_inv = ajuste;

            for (int j = 1; j < ajuste/2; j = j + 3)
            {   
                rota_inverter[i].distancia = rota_inverter[i].distancia
                - grafo[rota[i].percurso[j]][rota[i].percurso[j - 1]]
                - grafo[rota[i].percurso[j]][rota[i].percurso[j + 1]]
                - grafo[rota[i].percurso[aux_inv]][rota[i].percurso[aux_inv + 1]]
                - grafo[rota[i].percurso[aux_inv]][rota[i].percurso[aux_inv - 1]]
                + grafo[rota[i].percurso[aux_inv]][rota[i].percurso[j - 1]]
                + grafo[rota[i].percurso[aux_inv]][rota[i].percurso[j + 1]]
                + grafo[rota[i].percurso[j]][rota[i].percurso[aux_inv - 1]]
                + grafo[rota[i].percurso[j]][rota[i].percurso[aux_inv + 1]];


                //printf("Antes: %d -> %d, ", rota[i].percurso[j], rota[i].percurso[j + 1]);
                aux = rota[i].percurso[j];
                rota_inverter[i].percurso[j] = rota[i].percurso[aux_inv];
                rota_inverter[i].percurso[aux_inv] = aux;
                //printf("Depois: %d -> %d\n", rota_inverter[i].percurso[j], rota_inverter[i].percurso[j + 1]);

                if (rota_inverter[i].distancia > distancia_anterior)
                {
                    rota_inverter[i].percurso = rota[i].percurso;
                    // for (int k = 0; k < rota_inverter[i].tamanho_percurso; k++)
                    // {
                    //     rota_inverter[i].percurso[k] = rota_aux[k];
                    // }
                    // rota_inverter[i].distancia = distancia_anterior;
                }
                aux_inv--;
            }
            free(rota_aux);
        }
        //Print_Percurso(rota_inverter[i].percurso, rota_inverter[i].tamanho_percurso);
    }

    return rota_inverter;  
}

/*struct rota_veiculo Dois_OPT(int **grafo, struct rota_veiculo rota)
{    
    //printf("2OPT:\n");
    int aux, aux2, distancia_anterior = 0;
    struct rota_veiculo nova_rota = (struct rota_veiculo*)malloc(sizeof(struct rota_veiculo));

    nova_rota.percurso = (int*)malloc(sizeof(int)*dimensao);
    for (int b = 0; b < rota.tamanho_percurso; b++)
    {
        //printf("Debug 1 --- rota[%d].percurso[%d]: %d\n", i, b, rota.percurso[b]);
        nova_rota.percurso[b] = rota.percurso[b];
        //printf("Debug 2 --- nova_rota[%d].percurso[%d]: %d --- rota[%d].percurso[%d]: %d\n\n", i, b, nova_rota.percurso[b], i, b, rota.percurso[b]);
    }
    nova_rota.distancia = rota.distancia;
    nova_rota.carga = rota.carga;
    nova_rota.tamanho_percurso = rota.tamanho_percurso;

    distancia_anterior = nova_rota.distancia;

    srand(time(NULL));

    int ajuste = nova_rota.tamanho_percurso/((rand() % 5) + 2);
    if(nova_rota.tamanho_percurso >= 6)
    {            
        int *rota_aux = (int*)malloc(sizeof(int)*dimensao);
        for (int m = 0; m < nova_rota.tamanho_percurso; m++)
        {
            rota_aux[m] = nova_rota.percurso[m];
        }
        
        //printf("Ajuste: %d\n", ajuste);
        //Print_Percurso(nova_rota.percurso, nova_rota.tamanho_percurso);
        int j;
        for (j = 1; j < ajuste; j = j + 3)
        {   
            nova_rota.distancia = nova_rota.distancia
            - grafo[nova_rota.percurso[j]][nova_rota.percurso[j - 1]]
            - grafo[nova_rota.percurso[j + 3]][nova_rota.percurso[j + 4]]
            + grafo[nova_rota.percurso[j + 3]][nova_rota.percurso[j - 1]]
            + grafo[nova_rota.percurso[j]][nova_rota.percurso[j + 4]];

            //printf("Antes: %d -> %d -> %d -> %d, ", nova_rota.percurso[j], nova_rota.percurso[j + 1], nova_rota.percurso[j + 2], nova_rota.percurso[j + 3]);
            aux = nova_rota.percurso[j];
            aux2 = nova_rota.percurso[j + 1];
            nova_rota.percurso[j] = nova_rota.percurso[j + 3];
            nova_rota.percurso[j + 1] = nova_rota.percurso[j + 2];
            nova_rota.percurso[j + 2] = aux2;
            nova_rota.percurso[j + 3] = aux;
            //printf("Depois: %d -> %d -> %d -> %d\n", nova_rota.percurso[j], nova_rota.percurso[j + 1], nova_rota.percurso[j + 2], nova_rota.percurso[j + 3]);
            
        }
        //Print_Percurso(nova_rota.percurso, nova_rota.tamanho_percurso);
        //printf("Distancia anterior: %d, ", distancia_anterior);

        //printf("Distancia calculada: %d, distancia verdadeira: %d\n---------------------\n", nova_rota.distancia, Distancia(nova_rota.percurso, grafo, nova_rota.tamanho_percurso));

        if (nova_rota.distancia > distancia_anterior)
        {
            nova_rota.percurso = rota_aux;
            nova_rota.distancia = distancia_anterior;
        }
        free(rota_aux);
    }    

    return nova_rota;
}

struct rota_veiculo Inverter(int **grafo, struct rota_veiculo rota)
{
    //printf("Inverter:\n");
    int aux, distancia_anterior = 0;
    struct rota_veiculo *nova_rota = (struct rota_veiculo*)malloc(sizeof(struct rota_veiculo)*veiculos);

    nova_rota.percurso = (int*)malloc(sizeof(int)*dimensao);        
    for (int b = 0; b < rota.tamanho_percurso; b++)
    {
        //printf("Debug 1 --- rota[%d].percurso[%d]: %d\n", i, b, rota.percurso[b]);
        nova_rota.percurso[b] = rota.percurso[b];
        //printf("Debug 2 --- nova_rota[%d].percurso[%d]: %d --- rota[%d].percurso[%d]: %d\n\n", i, b, nova_rota.percurso[b], i, b, rota.percurso[b]);
    }
    nova_rota.distancia = rota.distancia;
    nova_rota.carga = rota.carga;
    nova_rota.tamanho_percurso = rota.tamanho_percurso;

    distancia_anterior = nova_rota.distancia;

    srand(time(NULL));

    int ajuste = nova_rota.tamanho_percurso/((rand() % 4) + 2);
    //Print_Percurso(nova_rota.percurso, nova_rota.tamanho_percurso);
    if(nova_rota.tamanho_percurso >= 4)
    {
        int *rota_aux = (int*)malloc(sizeof(int)*dimensao);
        for (int m = 0; m < nova_rota.tamanho_percurso; m++)
        {
            rota_aux[m] = nova_rota.percurso[m];
        }

        //printf("Ajuste: %d\n", ajuste);
        int j, reverter = ajuste;
        for (j = 1; j < ajuste/2; j = j + 2)
        {   
            nova_rota.distancia = nova_rota.distancia
            - grafo[nova_rota.percurso[j]][nova_rota.percurso[j - 1]]
            - grafo[nova_rota.percurso[j]][nova_rota.percurso[j + 1]]
            - grafo[nova_rota.percurso[reverter]][nova_rota.percurso[reverter - 1]]
            - grafo[nova_rota.percurso[reverter]][nova_rota.percurso[reverter + 1]]
            + grafo[nova_rota.percurso[reverter + 1]][nova_rota.percurso[j - 1]]
            + grafo[nova_rota.percurso[reverter]][nova_rota.percurso[j + 1]];
            + grafo[nova_rota.percurso[j]][nova_rota.percurso[reverter - 1]];
            + grafo[nova_rota.percurso[j]][nova_rota.percurso[reverter + 1]];

            //printf("Antes: %d -> %d, ", nova_rota.percurso[j], nova_rota.percurso[reverter]);
            aux = nova_rota.percurso[j];
            nova_rota.percurso[j] = nova_rota.percurso[reverter];
            nova_rota.percurso[reverter] = aux;
            //printf("Depois: %d -> %d\n", nova_rota.percurso[j], nova_rota.percurso[reverter]);
            reverter--;
            
        }
        //Print_Percurso(nova_rota.percurso, nova_rota.tamanho_percurso);
        //printf("Distancia anterior: %d, ", distancia_anterior);

        //printf("Distancia calculada: %d, distancia verdadeira: %d\n--------------------\n", nova_rota.distancia, Distancia(nova_rota.percurso, grafo, nova_rota.tamanho_percurso));

        if (nova_rota.distancia > distancia_anterior)
        {
            nova_rota.percurso = rota_aux;
            nova_rota.distancia = distancia_anterior;
        }
        free(rota_aux);
    }    

    return nova_rota;
}

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
}*/

/*struct nova_rota_veiculo *VNN(int **grafo, struct nova_rota_veiculo *nova_rota)
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