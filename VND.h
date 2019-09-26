#ifndef __VND_H_
#define __VND_H_

#include "refinamento.h"
#include "gulosa.h"

#define NUM_VIZINHANCAS 3
#define V_SWAP 0
#define V_TWOOPT 1
#define V_INV 2
#define VAZIO 0;

vector<rota_veiculo> VND (vector<rota_veiculo> solucao_gulosa, double **grafo){
    
    int k_vizinhancas = 0, i=0;
    //int nveiculos = 3;
    
    vector<rota_veiculo> solucao_atual = solucao_gulosa;
    vector<rota_veiculo> melhor_solucao = solucao_gulosa;

    //solucao_atual[1].distancia = 0;
    //melhor_solucao[1].distancia = INT_MAX;

    for ( k_vizinhancas = 0; k_vizinhancas < NUM_VIZINHANCAS; k_vizinhancas++)
    {
        switch (k_vizinhancas)
        {
            case V_SWAP:
               solucao_atual = SWAP(grafo, solucao_gulosa);
             
                break;
            case V_TWOOPT:
               solucao_atual = DoitOPT(grafo, solucao_gulosa);

                break;
            case V_INV:
                solucao_atual = Inverter(grafo, solucao_gulosa);

                break;
            default:
                break;
        }

        for(i=0; i< melhor_solucao.size(); i++){
            if(solucao_atual[i].distancia < melhor_solucao[i].distancia /*f(s') > f(s'') */){
               
                melhor_solucao[i] = solucao_atual[i];
            
            }

        }


    }
    
    
    return melhor_solucao; /* s' otimo */
}



#endif